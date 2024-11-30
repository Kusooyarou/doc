#include <generators/simple/SimpleGenerators.hpp>

#include "RandLevelExperimentalGenerator.hpp"

namespace DbGenerators {

RandLevelExperimentalGenerator::RandLevelExperimentalGenerator(
    const GenerationParameters& i_param
) :
  SimpleGeneratorBase(i_param) {}

GraphPtr RandLevelExperimentalGenerator::generate() const {
  auto             param = getParameters();

  SimpleGenerators generator(param.getSeed());
  generator.setGatesInputsInfo(param.getGatesInputsInfo());

  // auto start = high_resolution_clock::now();

  return generator.generatorRandLevelExperimental(
      param.getRandLevel().getMinLevel(),
      param.getRandLevel().getMaxLevel(),
      param.getRandLevel().getMinElements(),
      param.getRandLevel().getMaxElements(),
      param.getInputs(),
      param.getOutputs()
  );

  // auto    stop     = high_resolution_clock::now();
  // auto    duration = duration_cast<microseconds>(stop - start);
  // std::clog << "Time taken on experimental: " << duration.count()
  //            << " microseconds" << std::endl;
}

}  // namespace DbGenerators
