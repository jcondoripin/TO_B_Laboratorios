#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include "InputProcessor.h"
#include "CalculatorCore.h"

using namespace std;

void runTests()
{
  InputProcessor inp(6);
  CalculatorCore core;

  {
    auto t = inp.tokenize("2+3+5");
    assert(core.evaluateTokens(t) == 10);
  }
  {
    auto t = inp.tokenize("10-4");
    assert(core.evaluateTokens(t) == 6);
  }
  {
    auto t = inp.tokenize("3*4");
    assert(core.evaluateTokens(t) == 12);
  }
  {
    auto t = inp.tokenize("8/2");
    assert(core.evaluateTokens(t) == 4);
  }

  // ---- Precedencia de operadores ----
  {
    auto t = inp.tokenize("2+3*4");
    assert(core.evaluateTokens(t) == 14);
  }
  {
    auto t = inp.tokenize("10-2*3");
    assert(core.evaluateTokens(t) == 4);
  }
  {
    auto t = inp.tokenize("100/10+5");
    assert(core.evaluateTokens(t) == 15);
  }

  // ---- Números negativos y unarios ----
  {
    auto t = inp.tokenize("-5+10");
    assert(core.evaluateTokens(t) == 5);
  }
  {
    auto t = inp.tokenize("3+-2+7");
    assert(core.evaluateTokens(t) == 8);
  }
  {
    auto t = inp.tokenize("-3*-2");
    assert(core.evaluateTokens(t) == 6);
  }

  // ---- Manejo de espacios ----
  {
    auto t = inp.tokenize("  12   +   3 +4 ");
    assert(core.evaluateTokens(t) == 19);
  }

  bool exceptionThrown = false;
  try
  {
    auto t = inp.tokenize("5/0");
    core.evaluateTokens(t);
  }
  catch (const exception &e)
  {
    exceptionThrown = true;
    string msg = e.what();
    assert(msg.find("División por cero") != string::npos);
  }
  assert(exceptionThrown);
  
  cout << "✅ Todas las pruebas pasaron correctamente." << endl;
}

int main()
{
  runTests();
  return 0;
}
