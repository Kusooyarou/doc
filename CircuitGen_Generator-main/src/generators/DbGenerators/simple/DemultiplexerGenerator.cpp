#include "DemultiplexerGenerator.hpp"
#include <generators/simple/PlexerGenerator.hpp>

namespace DbGenerators {

DemultiplexerGenerator::DemultiplexerGenerator(
    const GenerationParameters& i_param
) :
  SimpleGeneratorBase(i_param) {}

GraphPtr DemultiplexerGenerator::generate() const {
  auto             param = getParameters();

  PlexerGenerator  sg(param);

  int32_t i_bits = param.getOutputs();
  return sg.generatorDemultiplexer(i_bits);
}

}  // namespace DbGenerators
