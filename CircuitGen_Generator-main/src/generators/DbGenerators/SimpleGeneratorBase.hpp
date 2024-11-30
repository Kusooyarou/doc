#pragma once
#include <memory>
#include <CircuitGenGraph/OrientedGraph.hpp>
#include <generators/GenerationParameters.hpp>

namespace DbGenerators {
  class SimpleGeneratorBase {
  public:
    SimpleGeneratorBase(const GenerationParameters& i_param);

    virtual GraphPtr      generate() const = 0;

    GenerationParameters& getParameters() const { return *parameters.get(); }

  private:
    std::shared_ptr<GenerationParameters> parameters;
  };
}
