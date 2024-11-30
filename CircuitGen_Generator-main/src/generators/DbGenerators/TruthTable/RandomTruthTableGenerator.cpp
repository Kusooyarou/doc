#include "RandomTruthTableGenerator.hpp"
#include <generators/simple/FromTruthTableGenerator.hpp>

namespace DbGenerators {
  RandomTruthTableGenerator::RandomTruthTableGenerator(
      const GenerationParameters& i_param
  ) :
    GeneratorBase(i_param) {}

  std::vector<GraphPtr> RandomTruthTableGenerator::generate() const {
    auto             param = getParameters();

    std::vector<GraphPtr> allGraphs;

    TruthTable            tt(param.getInputs(), param.getOutputs(), 0.0);

    if (param.getZhegalkin().getZhegalkin()) {
      auto graph = FromTruthTableGenerator(param).zhegalkinFromTruthTable(tt);
      graph->setName(param.getName() + "_" + "Zhegalkin");
      allGraphs.push_back(graph);
    }
    if (param.getCNF().getCNFF()) {
      auto graph = FromTruthTableGenerator(param).cnfFromTruthTable(tt, !param.getCNF().getCNFF());
      graph->setName(param.getName() + "_" + "CNFF");
      allGraphs.push_back(graph);
    }
    if (param.getCNF().getCNFT()) {
      auto graph = FromTruthTableGenerator(param).cnfFromTruthTable(tt, param.getCNF().getCNFT());
      graph->setName(param.getName() + "_" + "CNFT");
      allGraphs.push_back(graph);
    }

    return allGraphs;
  }
}