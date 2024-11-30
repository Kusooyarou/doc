#pragma once
#include <memory>
#include <vector>

#include <CircuitGenGraph/OrientedGraph.hpp>
#include <generators/GenerationParameters.hpp>

namespace DbGenerators {
  class GeneratorBase {
  public:
    GeneratorBase(const GenerationParameters& i_param);

    virtual std::vector<GraphPtr> generate() const = 0;

    GenerationParameters& getParameters() const { return *parameters.get(); }

  private:
    std::shared_ptr<GenerationParameters> parameters;
  };
}
