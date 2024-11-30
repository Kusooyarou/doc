#include "GeneratorBase.hpp"

namespace DbGenerators {
  GeneratorBase::GeneratorBase(const GenerationParameters& i_param) :
    parameters(std::make_shared<GenerationParameters>(i_param)) {}
}