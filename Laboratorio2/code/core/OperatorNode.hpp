#pragma once
#include "../base/Node.hpp"
#include <string>

class OperatorNode : public Node
{
protected:
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

public:
  OperatorNode(std::unique_ptr<Node> l, std::unique_ptr<Node> r) : left(std::move(l)), right(std::move(r)) {}
  virtual char symbol() const = 0;

  virtual int precedence() const = 0;

  virtual bool isValidInContext(const std::string &fullExpr, size_t opPos) const = 0;

  double evaluate() const override = 0;

  std::string toString() const override = 0;

  void stepEvaluate(std::vector<std::string> &steps) const
  {
    left->stepEvaluate(steps);
    right->stepEvaluate(steps);
    double lval = left->evaluate();
    double rval = right->evaluate();
    std::ostringstream oss;
    oss << lval << " " << symbol() << " " << rval << " = " << evaluate();
    steps.push_back(oss.str());
  };
};