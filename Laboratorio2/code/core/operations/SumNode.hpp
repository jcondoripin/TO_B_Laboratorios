#pragma once
#include "../OperatorNode.hpp"
#include <memory>
#include <cctype>

class SumNode : public OperatorNode
{
public:
  SumNode(std::unique_ptr<Node> l, std::unique_ptr<Node> r) : OperatorNode(std::move(l), std::move(r)) {}
  char symbol() const override { return '+'; }
  int precedence() const override { return 1; }
  bool isValidInContext(const std::string &expr, size_t pos) const override
  {
    if (pos == 0 || pos + 1 >= expr.size())
      return false;
    char before = expr[pos - 1];
    char after = expr[pos + 1];
    if (before == '+' || after == '+')
      return false;
    bool isOperandBefore = std::isdigit(before) || before == '.' || before == ')';
    bool isOperandAfter = std::isdigit(after) || after == '.' || after == '(' || after == '-';
    return isOperandBefore && isOperandAfter;
  }
  double evaluate() const override { return left->evaluate() + right->evaluate(); }
  void printInorder(std::ostream &os) const override
  {
    left->printInorder(os);
    os << " + ";
    right->printInorder(os);
  }
  void printPreorder(std::ostream &os) const override
  {
    os << "+ ";
    left->printPreorder(os);
    right->printPreorder(os);
  }
  void printPostorder(std::ostream &os) const override
  {
    left->printPostorder(os);
    right->printPostorder(os);
    os << " +";
  }
  std::string toString() const override { return "(" + left->toString() + " + " + right->toString() + ")"; }
};