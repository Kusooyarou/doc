#include "MultiplexerGenerator.hpp"
#include <generators/simple/PlexerGenerator.hpp>

namespace DbGenerators {

MultiplexerGenerator::MultiplexerGenerator(const GenerationParameters& i_param
) :
  SimpleGeneratorBase(i_param) {}

GraphPtr MultiplexerGenerator::generate() const {
  auto             param = getParameters();

  PlexerGenerator  sg(param);

  int32_t i_bits = param.getInputs();
  return sg.generatorMultiplexer(i_bits);
}

}  // namespace DbGenerators
