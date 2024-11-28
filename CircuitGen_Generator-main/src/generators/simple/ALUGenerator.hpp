#pragma once
#include <generators/simple/SimpleGeneratorBase.hpp>

class ALUGenerator : public SimpleGeneratorBase {
public:
  ALUGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};