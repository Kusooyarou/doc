#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class EncoderGenerator : public SimpleGeneratorBase {
public:
  EncoderGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};