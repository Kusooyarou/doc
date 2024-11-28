#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class ParityGenerator : public SimpleGeneratorBase {
public:
  ParityGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};