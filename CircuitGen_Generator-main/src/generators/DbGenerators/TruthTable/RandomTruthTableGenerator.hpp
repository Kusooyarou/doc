#pragma once
#include <generators/DbGenerators/GeneratorBase.hpp>

namespace DbGenerators {
  class RandomTruthTableGenerator : public GeneratorBase {
  public:
    RandomTruthTableGenerator(const GenerationParameters& i_param);

    std::vector<GraphPtr> generate() const;
  };
}