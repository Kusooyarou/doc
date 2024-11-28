#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class SubtractorGenerator : public SimpleGeneratorBase {
public:
  SubtractorGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};