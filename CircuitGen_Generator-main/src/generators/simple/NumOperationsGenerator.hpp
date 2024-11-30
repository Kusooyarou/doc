#pragma once
#include <generators/simple/SimpleGenerator.hpp>

class NumOperationsGenerator : public SimpleGenerator {
public:
  NumOperationsGenerator(const GenerationParameters& i_param);

  GraphPtr generatorNumOperation(
      uint32_t                 i_input,
      uint32_t                 i_output,
      std::map<Gates, int32_t> i_logicOper,
      bool                     i_leaveEmptyOut = true
  );
};