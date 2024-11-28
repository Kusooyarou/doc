#pragma once

#include <generators/GeneratorBase.hpp>

class RandomTruthTableGenerator : public GeneratorBase {
public:
  RandomTruthTableGenerator(const GenerationParameters& i_param);

  std::vector<GraphPtr> generate() const;
};