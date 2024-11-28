#include "GeneticTruthTableGenerator.hpp"
#include <baseStructures/truthTable/TruthTable.hpp>
#include <generators/Genetic/GeneticParameters.hpp>
#include <generators/Genetic/GenGenerator.hpp>

GeneticTruthTableGenerator::GeneticTruthTableGenerator(
    const GenerationParameters& i_param
) :
  GeneratorBase(i_param) {}

std::vector<GraphPtr> GeneticTruthTableGenerator::generate() const {
  auto             param = getParameters();

  GeneticGenerator<TruthTable, TruthTableParameters> gg(
      GeneticParameters(param.getGenetic()),
      {param.getInputs(), param.getOutputs()},
      //d_mainPath,
      param.getName()
  );

  const auto& population = gg.generate();
  auto        graphs     = gg.getGraphsFromPopulation(population);

  return graphs;
}
