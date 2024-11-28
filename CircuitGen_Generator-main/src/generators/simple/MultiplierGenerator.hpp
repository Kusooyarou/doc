#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class MultiplierGenerator : public SimpleGeneratorBase {
public:
  MultiplierGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};