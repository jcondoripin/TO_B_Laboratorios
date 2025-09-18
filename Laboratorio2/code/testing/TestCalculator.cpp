#include "TestCalculator.h"
#include <iostream>
#include <cmath>
#include <cassert>

bool TestCalculator::testExpression(const Calculator &calc, const std::string &expr, double expected, const std::string &testName)
{
  Calculator tempCalc = calc;
  double result = tempCalc.compute(expr);
  bool passed = std::abs(result - expected) < 0.01 && !std::isnan(result);

  if (!passed)
  {
    std::string errorMessage = testName + " failed. Expected: " + std::to_string(expected) + " Got: " + std::to_string(result);
    assert(passed && errorMessage.c_str());
  }

  return passed;
}

bool TestCalculator::testInvalidExpression(const Calculator &calc, const std::string &expr, const std::string &testName)
{
  Calculator tempCalc = calc;
  double result = tempCalc.compute(expr);
  bool passed = std::isnan(result);

  if (!passed)
  {
    std::string errorMessage = testName + " failed. Expected: Error, Got: " + std::to_string(result);
    assert(passed && errorMessage.c_str());
  }

  return passed;
}

void TestCalculator::runTests()
{
  Calculator calc;
  int passed = 0, total = 0;

  total++;
  if (testExpression(calc, "1+2", 3.0, "Test Addition"))
    passed++;

  total++;
  if (testExpression(calc, "5-2", 3.0, "Test Subtraction"))
    passed++;

  total++;
  if (testExpression(calc, "2*3", 6.0, "Test Multiplication"))
    passed++;

  total++;
  if (testExpression(calc, "6/2", 3.0, "Test Division"))
    passed++;

  total++;
  if (testExpression(calc, "(1+2)*3", 9.0, "Test Parentheses"))
    passed++;

  total++;
  if (testExpression(calc, "2+3*4", 14.0, "Test Precedence"))
    passed++;

  total++;
  if (testExpression(calc, "-2+5", 3.0, "Test Unary Minus"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "1//2", "Test Invalid Division"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "+2", "Test Leading Operator"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "1**2", "Test Consecutive Multiply"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "1+", "Test Trailing Operator"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "(1+2", "Test Mismatched Parentheses"))
    passed++;

  total++;
  if (testInvalidExpression(calc, "1/0", "Test Division by Zero"))
    passed++;

  std::cout << "\nTest Summary: " << passed << "/" << total << " tests passed.\n";
}
