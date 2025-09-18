#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include "CalculatorCore.h"

class InputProcessor
{
public:
  InputProcessor(size_t maxNumbers = 6) : maxNumbers(maxNumbers) {}
  std::vector<CalculatorCore::Token> tokenize(const std::string &input);

private:
  size_t maxNumbers;
};

#endif