#include "SummatorGenerator.hpp"
#include <generators/simple/ArithmeticGenerator.hpp>

namespace DbGenerators {

SummatorGenerator::SummatorGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr SummatorGenerator::generate() const {
  auto             param = getParameters();

  ArithmeticGenerator sg(param);

  int32_t bits        = param.getInputs();
  bool    overflowIn  = param.getSummator().getOverFlowIn();
  bool    overflowOut = param.getSummator().getOverFlowOut();
  bool    minus       = param.getSummator().getMinus();
  return sg.generatorSummator(bits, overflowIn, overflowOut, minus);
}

}  // namespace DbGenerators
