#include "RandLevelGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

namespace DbGenerators {

RandLevelGenerator::RandLevelGenerator(const GenerationParameters& i_param) :
  SimpleGeneratorBase(i_param) {}

GraphPtr RandLevelGenerator::generate() const {
  auto             param = getParameters();

  SimpleGenerators generator(param.getSeed());
  generator.setGatesInputsInfo(param.getGatesInputsInfo());

  return generator.generatorRandLevel(
      param.getRandLevel().getMinLevel(),
      param.getRandLevel().getMaxLevel(),
      param.getRandLevel().getMinElements(),
      param.getRandLevel().getMaxElements(),
      param.getInputs(),
      param.getOutputs()
  );
}

}  // namespace DbGenerators
