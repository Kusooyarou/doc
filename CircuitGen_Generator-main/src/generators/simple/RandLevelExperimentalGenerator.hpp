#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class RandLevelExperimentalGenerator : public SimpleGeneratorBase {
public:
  RandLevelExperimentalGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};
