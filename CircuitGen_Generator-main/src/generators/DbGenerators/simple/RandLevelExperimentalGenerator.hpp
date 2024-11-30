#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class RandLevelExperimentalGenerator : public SimpleGeneratorBase {
public:
  RandLevelExperimentalGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};

}  // namespace DbGenerators
