#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class DecoderGenerator : public SimpleGeneratorBase {
public:
  DecoderGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};