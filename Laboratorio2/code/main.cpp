#include "interface/Menu.hpp"
#include "controller/Calculator.hpp"

int main()
{
  Calculator calc;
  Menu::run(calc);
  return 0;
}