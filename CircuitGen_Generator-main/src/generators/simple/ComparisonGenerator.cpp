#include "ComparisonGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

ComparisonGenerator::ComparisonGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr ComparisonGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  int32_t  i_bits   = param.getInputs();
  bool     compare0 = param.getComparison().getCompare0();
  bool     compare1 = param.getComparison().getCompare1();
  bool     compare2 = param.getComparison().getCompare2();
  return sg.generatorComparison(i_bits, compare0, compare1, compare2);
}
