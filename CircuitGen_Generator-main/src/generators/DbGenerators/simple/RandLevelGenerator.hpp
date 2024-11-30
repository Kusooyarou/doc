#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class RandLevelGenerator : public SimpleGeneratorBase {
public:
  RandLevelGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};

}  // namespace DbGenerators