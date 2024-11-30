#include "EncoderGenerator.hpp"
#include <generators/simple/CoderGenerator.hpp>

namespace DbGenerators {

EncoderGenerator::EncoderGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr EncoderGenerator::generate() const {
  auto             param = getParameters();

  CoderGenerator   sg(param);

  int32_t i_bits = param.getInputs();
  return sg.generatorEncoder(i_bits);
}

}  // namespace DbGenerators
