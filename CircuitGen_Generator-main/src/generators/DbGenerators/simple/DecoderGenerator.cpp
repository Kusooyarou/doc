#include "DecoderGenerator.hpp"
#include <generators/simple/CoderGenerator.hpp>

namespace DbGenerators {

DecoderGenerator::DecoderGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr DecoderGenerator::generate() const {
  auto             param = getParameters();

  CoderGenerator   sg(param);

  return sg.generatorDecoder(param.getInputs());
}

}  // namespace DbGenerators