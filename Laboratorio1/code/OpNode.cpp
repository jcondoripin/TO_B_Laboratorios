#include "OpNode.h"

double BinaryNode::eval() const
{
  double L = left->eval();
  double R = right->eval();
  switch (op)
  {
  case '+':
    return L + R;
  case '-':
    return L - R;
  case '*':
    return L * R;
  case '/':
    if (R == 0.0)
      throw std::runtime_error("División por cero");
    return L / R;
  default:
    throw std::runtime_error("Operador desconocido");
  }
}
