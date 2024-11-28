#include "EncoderGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

EncoderGenerator::EncoderGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr EncoderGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  int32_t i_bits = param.getInputs();
  return sg.generatorEncoder(i_bits);
}
