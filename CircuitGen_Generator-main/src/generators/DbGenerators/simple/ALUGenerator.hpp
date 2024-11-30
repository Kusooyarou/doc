#pragma once
#include <generators/DbGenerators/SimpleGeneratorBase.hpp>

namespace DbGenerators {

class ALUGenerator : public SimpleGeneratorBase {
public:
	ALUGenerator(const GenerationParameters& i_param);

	GraphPtr generate() const;
};

}  // namespace DbGenerators