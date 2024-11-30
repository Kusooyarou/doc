#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class SubtractorGenerator : public SimpleGeneratorBase {
public:
  SubtractorGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};

}  // namespace DbGenerators