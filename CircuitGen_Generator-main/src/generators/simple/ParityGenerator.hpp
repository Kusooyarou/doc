#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class ParityGenerator : public SimpleGenerator {
public:
  ParityGenerator(const GenerationParameters& i_param);

  GraphPtr generatorParity(uint32_t i_bits);
};