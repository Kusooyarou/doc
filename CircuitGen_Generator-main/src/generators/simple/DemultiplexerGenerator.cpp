#include "DemultiplexerGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

DemultiplexerGenerator::DemultiplexerGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr DemultiplexerGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  int32_t i_bits = param.getOutputs();
  return sg.generatorDemultiplexer(i_bits);
}
