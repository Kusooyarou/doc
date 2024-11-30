#include <algorithm>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <climits>
#include <vector>

#include "DataBaseGenerator.hpp"

#include <additional/AuxiliaryMethods.hpp>
#include <additional/filesTools/FilesTools.hpp>
#include <baseStructures/Parser.hpp>
#include <circuit/Circuit.hpp>
#include <circuit/CircuitParameters.hpp>
#include <CircuitGenGenerator/ThreadPool.hpp>
#include <generators/DbGenerators/simple/RandLevelGenerator.hpp>
#include <generators/DbGenerators/simple/RandLevelExperimentalGenerator.hpp>
#include <generators/DbGenerators/TruthTable/RandomTruthTableGenerator.hpp>
#include <generators/DbGenerators/simple/NumOperationsGenerator.hpp>
#include <generators/DbGenerators/simple/SummatorGenerator.hpp>
#include <generators/DbGenerators/simple/ComparisonGenerator.hpp>
#include <generators/DbGenerators/simple/EncoderGenerator.hpp>
#include <generators/DbGenerators/simple/ParityGenerator.hpp>
#include <generators/DbGenerators/simple/SubtractorGenerator.hpp>
#include <generators/DbGenerators/simple/MultiplexerGenerator.hpp>
#include <generators/DbGenerators/simple/DemultiplexerGenerator.hpp>
#include <generators/DbGenerators/simple/MultiplierGenerator.hpp>
#include <generators/DbGenerators/simple/DecoderGenerator.hpp>
#include <generators/DbGenerators/simple/ALUGenerator.hpp>
#include <generators/DbGenerators/GeneticTruthTableGenerator.hpp>

using namespace std::chrono;
using namespace Threading;

void DataBaseGenerator::runGeneratorByDefault(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  GenerationTypes gt = i_dbgp.getGenerationType();
  std::function<void(const GenerationParameters&)> generator =
      getGenerateMethod(gt);
  // TODO: make normal code
  std::string dir = d_settings->getDatasetPath();

  if (createIdDirectories)
    dir += "/" + i_dbgp.getGenerationParameters().getName() + "/"
         + i_dbgp.getGenerationParameters().getRequestId();
  // Creating nested directories
  std::filesystem::create_directories(dir);

  d_mainPath = dir + "/";
  d_dirCount = 0;

  if (std::filesystem::is_directory(dir)) {
    for (const auto item : FilesTools::getDirectories(dir)) {
      std::string s0  = item;
      auto        pos = s0.find(d_settings->getGenerationMethodPrefix(gt));

      if (pos == std::string::npos)
        continue;

      s0.replace(pos, d_settings->getGenerationMethodPrefix(gt).size(), "");

      auto jk = std::min(s0.find("_"), s0.find("."));
      if (jk == std::string::npos) {
        jk = s0.size();
      }

      s0         = s0.substr(0, jk);
      d_dirCount = std::max(
          d_dirCount,
          std::stoi(s0) + 1
      );  // TODO: in general code n is int32, is it really need?
    }
  }

  std::vector<std::uint_fast32_t> seeds(i_dbgp.getEachIteration());

  d_randGenerator.setSeed(AuxMethods::getRandSeed());

  auto randGeneratorLambda = [&]() {
    return d_randGenerator.getRandInt(0, INT_MAX);
  };
  // we create int sequence, which would give us different seeds for each repeat
  std::generate(seeds.begin(), seeds.end(), randGeneratorLambda);

  ThreadPool pool(parallel);

  for (int32_t i = i_dbgp.getMinInputs(); i <= i_dbgp.getMaxInputs(); ++i) {
    for (int32_t j = i_dbgp.getMinOutputs(); j <= i_dbgp.getMaxOutputs(); ++j) {
      auto iter = seeds.begin();
      d_parameters.setInputs(i);
      d_parameters.setOutputs(j);

      if (parallel > 1) {
        for (int32_t tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          d_parameters.setIteration(tt);
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(gt)
              + AuxMethods::intToStringWithZeroes(d_dirCount)
          );

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter + i + j);

          auto runGenerator = [generator, param]() { generator(param); };

          pool.submit(runGenerator);

          ++d_dirCount;
          ++iter;
        }
      } else {
        for (int32_t tt = 0; tt < i_dbgp.getEachIteration(); ++tt) {
          // TODO: it is that Rustam told about iteration?
          d_parameters.setIteration(tt);
          d_parameters.setName(
              d_settings->getGenerationMethodPrefix(gt)
              + AuxMethods::intToStringWithZeroes(d_dirCount)
          );

          GenerationParameters param = d_parameters.getGenerationParameters();
          param.setSeed(*iter + i + j);

          generator(param);

          ++d_dirCount;
          ++iter;
        }
      }
    }
  }
  pool.wait();
}

ResultGraph DataBaseGenerator::generateTypeForGraph(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  d_type = ReturnType::GRAPH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphs);
}

ResultPath DataBaseGenerator::generateTypeForPath(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  d_type = ReturnType::PATH;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);

  return std::make_pair(d_mainPath, d_generatedGraphsNames);
}

void DataBaseGenerator::generateTypeDefault(
    const DataBaseGeneratorParameters& i_dbgp,
    uint8_t                            parallel,
    bool                               createIdDirectories
) {
  d_type = ReturnType::DEFAULT;

  runGeneratorByDefault(i_dbgp, parallel, createIdDirectories);
}

void DataBaseGenerator::addDataToReturn(GraphPtr graph) {
  d_resWrite.lock();
  switch (d_type) {
    case ReturnType::GRAPH:
      d_generatedGraphs.push_back(graph);
      break;
    case ReturnType::PATH:
      d_generatedGraphsNames.push_back(graph->getName());
      break;
    default:
      break;
  }
  d_resWrite.unlock();
}

void DataBaseGenerator::circuitGeneration(
    const GraphPtr&             graph,
    const GenerationParameters& i_param
) {
  Circuit c(graph);
  c.setPath(d_mainPath);
  c.setCircuitName(graph->getName());
  c.generate(
      i_param.getMakeGraphMLClassic(),
      i_param.getMakeGraphMLPseudoABCD(),
      i_param.getMakeGraphMLOpenABCD()
  );

  addDataToReturn(graph);
}

void DataBaseGenerator::circuitGeneration(
    const std::vector<GraphPtr>& graphs,
    const GenerationParameters&  i_param
) {
  for (auto graph : graphs) {
    circuitGeneration(graph, i_param);
  }
}

void DataBaseGenerator::circuitGeneration(
    const GeneratorBase&        generator,
    const GenerationParameters& i_param
) {
  circuitGeneration(generator.generate(), i_param);
}

void DataBaseGenerator::circuitGeneration(
    const SimpleGeneratorBase&  generator,
    const GenerationParameters& i_param
) {
  auto graph = generator.generate();
  graph->setName(i_param.getName());
  circuitGeneration(graph, i_param);
}

void DataBaseGenerator::generateDataBaseFromRandomTruthTable(const GenerationParameters& i_param) {
  RandomTruthTableGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseRandLevel(const GenerationParameters& i_param) {
  RandLevelGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseRandLevelExperimental(const GenerationParameters& i_param) {
  RandLevelExperimentalGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseNumOperations(const GenerationParameters& i_param) {
  NumOperationsGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseGenetic(const GenerationParameters& i_param) {
  GeneticTruthTableGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseSummator(const GenerationParameters& i_param) {
  SummatorGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseComparison(const GenerationParameters& i_param) {
  ComparisonGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseEncoder(const GenerationParameters& i_param) {
  EncoderGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseParity(const GenerationParameters& i_param) {
  ParityGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseSubtractor(const GenerationParameters& i_param) {
  SubtractorGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseMultiplexer(const GenerationParameters& i_param) {
  MultiplexerGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseDemultiplexer(const GenerationParameters& i_param) {
  DemultiplexerGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseMultiplier(const GenerationParameters& i_param) {
  MultiplierGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseDecoder(const GenerationParameters& i_param) {
  DecoderGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

void DataBaseGenerator::generateDataBaseALU(const GenerationParameters& i_param) {
  ALUGenerator generator(i_param);
  circuitGeneration(generator, i_param);
}

// maybe this method should be rewritten using map with GenerationTypes and
// FuncAlias
std::function<void(const GenerationParameters&)>
    DataBaseGenerator::getGenerateMethod(const GenerationTypes i_methodType) {
  using FuncAlias = void (DataBaseGenerator::*)(const GenerationParameters&);
  FuncAlias generateMethodFunc = nullptr;

  switch (i_methodType) {
    case GenerationTypes::FromRandomTruthTable:
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseFromRandomTruthTable;
      break;
    case GenerationTypes::RandLevel:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseRandLevel;
      break;
    case GenerationTypes::RandLevelExperimental:
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseRandLevelExperimental;
      break;
    case GenerationTypes::NumOperation:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseNumOperations;
      break;
    case GenerationTypes::Genetic:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseGenetic;
      break;
    case GenerationTypes::Summator:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseSummator;
      break;
    case GenerationTypes::Comparison:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseComparison;
      break;
    case GenerationTypes::Encoder:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseEncoder;
      break;
    case GenerationTypes::Subtractor:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseSubtractor;
      break;
    case GenerationTypes::Multiplexer:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseMultiplexer;
      break;
    case GenerationTypes::Demultiplexer:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseDemultiplexer;
      break;
    case GenerationTypes::Multiplier:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseMultiplier;
      break;
    case GenerationTypes::Decoder:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseDecoder;
      break;
    case GenerationTypes::Parity:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseParity;
      break;
    case GenerationTypes::ALU:
      generateMethodFunc = &DataBaseGenerator::generateDataBaseALU;
      break;

    default:
      std::clog << "Something went wrong while getting generation method. "
                << "\"FromRandomTruthTable\" is set as generation method."
                << std::endl;
      generateMethodFunc =
          &DataBaseGenerator::generateDataBaseFromRandomTruthTable;
      break;
  }

  return std::bind(generateMethodFunc, this, std::placeholders::_1);
}