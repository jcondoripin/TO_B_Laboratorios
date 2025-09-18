#pragma once
#include "../base/Node.hpp"
#include <string>
#include <sstream>

class NumberNode : public Node
{
private:
  double value;

public:
  NumberNode(double val) : value(val) {}
  double evaluate() const override { return value; }
  void printInorder(std::ostream &os) const override { os << value; }
  void printPreorder(std::ostream &os) const override { os << value; }
  void printPostorder(std::ostream &os) const override { os << value; }
  std::string toString() const override { return std::to_string(value); }
  void stepEvaluate(std::vector<std::string> &steps) const override {}
};