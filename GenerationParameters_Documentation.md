
# Документация по файлу GenerationParameters.hpp

Файл `GenerationParameters.hpp` состоит из нескольких классов, которые позволяют настроить различные параметры генерации логических схем и конфигурации для генетических алгоритмов. В данной документации приведено описание каждого класса и его методов.

---

## Начало файла и подключение библиотек

```cpp
#pragma once
```
Указывает компилятору включать этот файл только один раз при компиляции, чтобы избежать ошибок повторного включения.

```cpp
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <generators/Genetic/GeneticParameters.hpp>
#include <settings/Settings.hpp>
```
Подключает стандартные библиотеки и пользовательские заголовочные файлы для работы с типами данных и конфигурацией генетических параметров и настроек.

---

## Класс `CNNFromTruthTableParameters`

Этот класс содержит параметры для генерации логических схем с использованием различных нормальных форм.

```cpp
class CNNFromTruthTableParameters {
public:
  bool getCNFF() { return d_CNFF; }
  bool getCNFT() { return d_CNFT; }
  void setCNFF(bool i_CNFF) { d_CNFF = i_CNFF; }
  void setCNFT(bool i_CNFT) { d_CNFT = i_CNFT; }
  void setLimit(bool i_limit) { d_generateLimitations = i_limit; }
```
Методы класса:
- `getCNFF()`, `getCNFT()`: Возвращают текущее значение параметров `CNFF` и `CNFT`.
- `setCNFF(bool i_CNFF)`, `setCNFT(bool i_CNFT)`: Устанавливают значения параметров `CNFF` и `CNFT`, определяющих, использовать ли конъюнктивную или дизъюнктивную нормальные формы.
- `setLimit(bool i_limit)`: Устанавливает параметр `generateLimitations`, накладывающий ограничения на генерируемые схемы.

```cpp
private:
  bool d_generateLimitations = false;
  bool d_CNFF                = false;
  bool d_CNFT                = false;
};
```
Переменные-члены:
- `d_generateLimitations`: Указывает, нужно ли накладывать ограничения на генерацию.
- `d_CNFF` и `d_CNFT`: Определяют использование конъюнктивной и дизъюнктивной нормальных форм.

---

## Класс `zhegalkinFromTruthTableParameters`

Этот класс задаёт параметры генерации с использованием полиномов Жегалкина.

```cpp
class zhegalkinFromTruthTableParameters {
public:
  bool getZhegalkin() { return d_zhegalkin; }
  void setZhegalkin(bool i_zhegalkin) { d_zhegalkin = i_zhegalkin; }

private:
  bool d_zhegalkin = false;
};
```
- `getZhegalkin()`: Возвращает текущее значение параметра `zhegalkin`.
- `setZhegalkin(bool i_zhegalkin)`: Устанавливает значение `zhegalkin`, управляющее использованием полиномов Жегалкина.

---

## Класс `GeneratorRandLevelParameters`

Этот класс отвечает за уровни и количество элементов на каждом уровне генерируемой структуры.

```cpp
class GeneratorRandLevelParameters {
public:
  uint32_t getMinLevel() const { return d_minLevel; }
  void     setMinLevel(uint32_t i_minLevel) { d_minLevel = i_minLevel; }
  uint32_t getMaxLevel() const { return d_maxLevel; }
  void     setMaxLevel(uint32_t i_maxLevel) { d_maxLevel = i_maxLevel; }
  uint32_t getMinElements() const { return d_minElements; }
  void setMinElements(uint32_t i_minElements) { d_minElements = i_minElements; }
  uint32_t getMaxElements() const { return d_maxElements; }
  void setMaxElements(uint32_t i_maxElements) { d_maxElements = i_maxElements; }
```
Методы для задания минимального и максимального уровня (`minLevel`, `maxLevel`) и количества элементов (`minElements`, `maxElements`) на уровне.

```cpp
private:
  uint32_t d_minLevel    = 0;
  uint32_t d_maxLevel    = 0;
  uint32_t d_minElements = 0;
  uint32_t d_maxElements = 0;
};
```
Переменные:
- `d_minLevel`, `d_maxLevel`: Минимальный и максимальный уровни структуры.
- `d_minElements`, `d_maxElements`: Минимальное и максимальное число элементов на каждом уровне.

---

## Класс `GeneratorNumOperationParameters`

Настраивает логические операции и их параметры для генерации схем.

```cpp
class GeneratorNumOperationParameters {
public:
  int32_t getLogicOper(const Gates& i_op) const {
    if (d_logicOper.find(i_op) != d_logicOper.end())
      return d_logicOper.at(i_op);
    return -1;
  }
  std::map<Gates, int32_t> getLogicOpers() const { return d_logicOper; }
  void setLogicOper(const std::pair<Gates, int32_t>& i_p) {
    d_logicOper[i_p.first] = i_p.second;
  }
  void setLogicOper(const std::map<Gates, int32_t>& i_p) { d_logicOper = i_p; }
  bool getLeaveEmptyOut() const { return d_leaveEmptyOut; }
  void setLeaveEmptyOut(bool i_leo) { d_leaveEmptyOut = i_leo; }
```
Методы:
- `getLogicOper(const Gates& i_op)`: Возвращает логическую операцию, если она присутствует в `d_logicOper`.
- `getLogicOpers()`: Возвращает все операции в `d_logicOper`.
- `setLogicOper`: Устанавливает пары значений операций.
- `getLeaveEmptyOut()`, `setLeaveEmptyOut()`: Управляют параметром `leaveEmptyOut`, указывающим, можно ли оставлять пустой выходной узел.

```cpp
private:
  std::map<Gates, int32_t> d_logicOper;
  bool                     d_leaveEmptyOut = true;
};
```

---

## Остальные классы параметров

Классы `GeneratorSummatorParameters`, `GeneratorComparisonParameters`, `GeneratorSubtractorParameters`, `GeneratorALUParameters` и другие, такие как `GenerationParameters`, имеют аналогичную структуру. Они содержат методы для работы с параметрами генерации, включают булевые флаги для различных видов логических операций и позволяют задавать или получать параметры.

---

## Класс `GenerationParameters`

Этот основной класс определяет параметры генерации, включая настройки входов, выходов, идентификатора запроса и другие данные.

```cpp
class GenerationParameters {
public:
  GenerationParameters(
      const std::string& i_name,
      const std::string& i_requestId,
      uint32_t           i_inputs,
      uint32_t           i_outputs,
      uint32_t           i_iteration,
      bool               i_makeGraphMLClassic   = false,
      bool               i_makeGraphMLPsedoABCD = false,
      bool               i_makeGraphMLOpenABCD  = false
  ) :
    d_name(i_name),
    d_requestId(i_requestId),
    d_inputs(i_inputs),
    d_outputs(i_outputs),
    d_iteration(i_iteration),
    d_makeGraphMLClassic(i_makeGraphMLClassic),
    d_makeGraphMLPseudoABCD(i_makeGraphMLPsedoABCD),
    d_makeGraphMLOpenABCD(i_makeGraphMLOpenABCD) {};
```
Конструктор задаёт основные параметры генерации, включая имя, количество входов и выходов, флаги `makeGraphML`, параметры графиков и другие параметры.

Методы для установки и получения:
- Имени генерации, количества входов/выходов, различных параметров графиков (`makeGraphML`), параметров для CNF, полиномов Жегалкина и др.

#### Дополнительные параметры

```cpp
void setRecombinationParameters(
      ParentsTypes       i_parentsTypes,
      uint32_t           i_tournamentNumber,
      RecombinationTypes i_recombinationType,
      uint32_t           i_refPoints,
      double             maskProbability,
      uint32_t           i_recombinationNumber
  )
```
Методы `setRecombinationParameters`, `setMutationParameters`, `setSelectionParameters` и другие позволяют задавать параметры для генетического алгоритма, такие как типы селекции, мутации и рекомбинации.

---

Каждый из этих классов помогает точно настраивать параметры генерации логических схем, уровня графов, операций и генетических алгоритмов для сложных комбинационных и арифметических схем.
