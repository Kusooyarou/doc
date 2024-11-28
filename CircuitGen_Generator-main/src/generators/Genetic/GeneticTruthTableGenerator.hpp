#pragma once

#include <generators/GeneratorBase.hpp>

class GeneticTruthTableGenerator : public GeneratorBase {
public:
  GeneticTruthTableGenerator(const GenerationParameters& i_param);

  std::vector<GraphPtr> generate() const;
};