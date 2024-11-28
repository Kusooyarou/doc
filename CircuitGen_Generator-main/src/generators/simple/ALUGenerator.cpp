#include "ALUGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

ALUGenerator::ALUGenerator(
    const GenerationParameters& i_param
) :
  SimpleGeneratorBase(i_param) {}

GraphPtr ALUGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators sg(param.getSeed());
  sg.setGatesInputsInfo(param.getGatesInputsInfo());

  return sg.generatorALU(
      param.getInputs(),
      param.getOutputs(),
      param.getALU().getALL(),
      param.getALU().getSUM(),
      param.getALU().getSUB(),
      param.getALU().getNSUM(),
      param.getALU().getNSUB(),
      param.getALU().getMULT(),
      param.getALU().getCOM(),
      param.getALU().getAND(),
      param.getALU().getNAND(),
      param.getALU().getOR(),
      param.getALU().getNOR(),
      param.getALU().getXOR(),
      param.getALU().getXNOR(),
      param.getALU().getCNF(),
      param.getALU().getRNL(),
      param.getALU().getNUMOP(),
      param.getALU().getminLevel(),
      param.getALU().getmaxLevel(),
      param.getALU().getminElement(),
      param.getALU().getmaxElement(),
      param.getALU().getm(),
      param.getALU().getLeaveEmptyOut()
  );
}
