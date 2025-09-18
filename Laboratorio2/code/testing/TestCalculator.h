#pragma once
#include "../controller/Calculator.hpp"

class TestCalculator
{
public:
  static void runTests();

private:
  static bool testExpression(const Calculator &calc, const std::string &expr, double expected, const std::string &testName);
  static bool testInvalidExpression(const Calculator &calc, const std::string &expr, const std::string &testName);
};