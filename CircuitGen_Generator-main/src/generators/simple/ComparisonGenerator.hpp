#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class ComparisonGenerator : public SimpleGeneratorBase {
public:
  ComparisonGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};