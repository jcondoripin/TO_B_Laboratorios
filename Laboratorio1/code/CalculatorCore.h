#ifndef CALCULATORCORE_H
#define CALCULATORCORE_H

#include <vector>
#include "OpNode.h"

class CalculatorCore
{
public:
  struct Token
  {
    bool isNumber;
    double number;
    char op;
    size_t pos;
  };

  CalculatorCore() = default;
  double evaluateTokens(const std::vector<Token> &tokens);
};

#endif 