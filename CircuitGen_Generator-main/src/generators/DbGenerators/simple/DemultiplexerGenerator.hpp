#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class DemultiplexerGenerator : public SimpleGeneratorBase {
public:
  DemultiplexerGenerator(const GenerationParameters& i_param);

  GraphPtr generate() const;
};

}  // namespace DbGenerators