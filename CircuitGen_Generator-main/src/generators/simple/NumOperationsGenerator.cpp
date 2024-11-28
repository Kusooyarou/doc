#include "NumOperationsGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

NumOperationsGenerator::NumOperationsGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr NumOperationsGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators generator(param.getSeed());
  generator.setGatesInputsInfo(param.getGatesInputsInfo());

  return generator.generatorNumOperation(
      param.getInputs(),
      param.getOutputs(),
      param.getNumOperations().getLogicOpers(),
      param.getNumOperations().getLeaveEmptyOut()
  );
}
