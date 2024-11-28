#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class NumOperationsGenerator : public SimpleGeneratorBase {
public:
  NumOperationsGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};