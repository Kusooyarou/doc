#pragma once
#include <generators/simple/SimpleGenerator.hpp>
#include <baseStructures/truthTable/TruthTable.hpp>

class FromTruthTableGenerator : public SimpleGenerator {
public:
  FromTruthTableGenerator(const GenerationParameters& i_param);

  GraphPtr cnfFromTruthTable(const TruthTable& i_table, bool i_tp = true);
  GraphPtr zhegalkinFromTruthTable(const TruthTable& i_table);
};
