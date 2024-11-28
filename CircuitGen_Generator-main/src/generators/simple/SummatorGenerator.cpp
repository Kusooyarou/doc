#include "SummatorGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

SummatorGenerator::SummatorGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr SummatorGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  int32_t  bits        = param.getInputs();
  bool     overflowIn  = param.getSummator().getOverFlowIn();
  bool     overflowOut = param.getSummator().getOverFlowOut();
  bool     minus       = param.getSummator().getMinus();
  return sg.generatorSummator(bits, overflowIn, overflowOut, minus);
}
