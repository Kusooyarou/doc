#include "DecoderGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

namespace DbGenerators {

DecoderGenerator::DecoderGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr DecoderGenerator::generate() const {
  auto             param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  return sg.generatorDecoder(param.getInputs());
}

}  // namespace DbGenerators