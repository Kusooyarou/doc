#include "MultiplierGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

MultiplierGenerator::MultiplierGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr MultiplierGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  return sg.generatorMultiplier(param.getInputs());
}
