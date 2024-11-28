#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class SummatorGenerator : public SimpleGeneratorBase {
public:
  SummatorGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};