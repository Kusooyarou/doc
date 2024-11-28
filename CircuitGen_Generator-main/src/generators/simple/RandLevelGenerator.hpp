#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class RandLevelGenerator : public SimpleGeneratorBase {
public:
  RandLevelGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};