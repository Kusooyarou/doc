#include "SimpleGeneratorBase.hpp"

namespace DbGenerators {
  SimpleGeneratorBase::SimpleGeneratorBase(const GenerationParameters& i_param
  ) :
    parameters(std::make_shared<GenerationParameters>(i_param)) {}
}
