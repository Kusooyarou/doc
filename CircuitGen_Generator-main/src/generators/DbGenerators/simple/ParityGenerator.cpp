#include "ParityGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

namespace DbGenerators {

ParityGenerator::ParityGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr ParityGenerator::generate() const {
  auto             param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  int32_t bits = param.getInputs();
  return sg.generatorParity(bits);
}

}  // namespace DbGenerators
