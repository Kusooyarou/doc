#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class DemultiplexerGenerator : public SimpleGeneratorBase {
public:
  DemultiplexerGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};