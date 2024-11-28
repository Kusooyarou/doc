#include "SubtractorGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

SubtractorGenerator::SubtractorGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr SubtractorGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  return sg.generatorSubtractor(
      param.getInputs(),
      param.getSubtractor().getOverFlowIn(),
      param.getSubtractor().getOverFlowOut(),
      param.getSubtractor().getSub()
  );
}
