#include "SubtractorGenerator.hpp"
#include <generators/simple/ArithmeticGenerator.hpp>

namespace DbGenerators {

SubtractorGenerator::SubtractorGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr SubtractorGenerator::generate() const {
  auto             param = getParameters();

  ArithmeticGenerator sg(param);

  return sg.generatorSubtractor(
      param.getInputs(),
      param.getSubtractor().getOverFlowIn(),
      param.getSubtractor().getOverFlowOut(),
      param.getSubtractor().getSub()
  );
}

}  // namespace DbGenerators
