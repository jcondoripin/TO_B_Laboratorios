#include "CalculatorCore.h"
#include <memory>
#include <stdexcept>

using namespace std;

double CalculatorCore::evaluateTokens(const vector<Token> &tokens)
{
  vector<Token> output;
  vector<char> opstack;

  auto prec = [](char op) -> int
  {
    if (op == '+' || op == '-')
      return 1;
    if (op == '*' || op == '/')
      return 2;
    return 0;
  };

  // Algoritmo shunting-yard para convertir a notación postfija
  for (const auto &t : tokens)
  {
    if (t.isNumber)
    {
      output.push_back(t);
    }
    else
    {
      char o1 = t.op;
      while (!opstack.empty() && prec(opstack.back()) >= prec(o1))
      {
        Token ot;
        ot.isNumber = false;
        ot.op = opstack.back();
        output.push_back(ot);
        opstack.pop_back();
      }
      opstack.push_back(o1);
    }
  }
  while (!opstack.empty())
  {
    Token ot;
    ot.isNumber = false;
    ot.op = opstack.back();
    output.push_back(ot);
    opstack.pop_back();
  }

  // Construcción del AST usando la jerarquía de operaciones
  vector<unique_ptr<OpNode>> stack;
  for (const auto &t : output)
  {
    if (t.isNumber)
    {
      stack.push_back(make_unique<NumberNode>(t.number));
    }
    else
    {
      if (stack.size() < 2)
        throw runtime_error("Expresión inválida: operador sin suficientes operandos");

      auto right = move(stack.back());
      stack.pop_back();
      auto left = move(stack.back());
      stack.pop_back();

      switch (t.op)
      {
      case '+':
        stack.push_back(make_unique<Suma>(move(left), move(right)));
        break;
      case '-':
        stack.push_back(make_unique<Resta>(move(left), move(right)));
        break;
      case '*':
        stack.push_back(make_unique<Multiplicacion>(move(left), move(right)));
        break;
      case '/':
        stack.push_back(make_unique<Division>(move(left), move(right)));
        break;
      default:
        throw runtime_error("Operador desconocido");
      }
    }
  }

  if (stack.size() != 1)
    throw runtime_error("Expresión inválida al construir AST");

  return stack.front()->eval();
}
