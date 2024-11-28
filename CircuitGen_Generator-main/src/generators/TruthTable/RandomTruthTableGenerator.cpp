#include "RandomTruthTableGenerator.hpp"
#include <generators/simple/SimpleGenerators.hpp>

RandomTruthTableGenerator::RandomTruthTableGenerator(
    const GenerationParameters& i_param
) :
  GeneratorBase(i_param) {}

std::vector<GraphPtr> RandomTruthTableGenerator::generate() const {
  auto param = getParameters();

  SimpleGenerators tftt(param.getSeed());
  tftt.setGatesInputsInfo(param.getGatesInputsInfo());

  std::vector<GraphPtr> allGraphs;

  TruthTable tt(param.getInputs(), param.getOutputs(), 0.0);

  if (param.getZhegalkin().getZhegalkin()) {
    auto graph = tftt.zhegalkinFromTruthTable(tt);
    graph->setName(param.getName() + "_" + "Zhegalkin");
    allGraphs.push_back(graph);
  }
  if (param.getCNF().getCNFF()) {
    auto graph = tftt.cnfFromTruthTable(tt, !param.getCNF().getCNFF());
    graph->setName(param.getName() + "_" + "CNFF");
    allGraphs.push_back(graph);
  }
  if (param.getCNF().getCNFT()) {
    auto graph = tftt.cnfFromTruthTable(tt, param.getCNF().getCNFT());
    graph->setName(param.getName() + "_" + "CNFT");
    allGraphs.push_back(graph);
  }

  return allGraphs;
}
