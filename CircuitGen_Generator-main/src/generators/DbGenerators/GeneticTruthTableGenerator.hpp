#pragma once
#include <generators/DbGenerators/GeneratorBase.hpp>

namespace DbGenerators {
  class GeneticTruthTableGenerator : public GeneratorBase {
  public:
    GeneticTruthTableGenerator(const GenerationParameters& i_param);

    std::vector<GraphPtr> generate() const;
  };
}