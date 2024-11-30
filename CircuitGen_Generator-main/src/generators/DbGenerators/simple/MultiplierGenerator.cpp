#include "MultiplierGenerator.hpp"
#include <generators/simple/ArithmeticGenerator.hpp>

namespace DbGenerators {

MultiplierGenerator::MultiplierGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr MultiplierGenerator::generate() const {
  auto             param = getParameters();

  ArithmeticGenerator sg(param);

  return sg.generatorMultiplier(param.getInputs());
}

}  // namespace DbGenerators
