#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class SummatorGenerator : public SimpleGeneratorBase {
public:
  SummatorGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};

}  // namespace DbGenerators