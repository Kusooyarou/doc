#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class MultiplexerGenerator : public SimpleGeneratorBase {
public:
  MultiplexerGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};