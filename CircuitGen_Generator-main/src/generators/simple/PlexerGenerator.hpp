#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class PlexerGenerator : public SimpleGenerator {
public:
  PlexerGenerator(const GenerationParameters& i_param);

  GraphPtr generatorMultiplexer(uint32_t i_bits);
  GraphPtr generatorDemultiplexer(uint32_t i_bits);
};
