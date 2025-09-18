#pragma once
#include "Node.hpp"
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

class ExpressionTree
{
private:
  std::unique_ptr<Node> root;

public:
  ExpressionTree() : root(nullptr) {}
  void setRoot(std::unique_ptr<Node> newRoot) { root = std::move(newRoot); }
  double evaluate() const
  {
    if (!root)
      throw std::runtime_error("Empty tree");
    return root->evaluate();
  }
  std::string toString() const
  {
    if (!root)
      return "";
    return root->toString();
  }
  void printInorder(std::ostream &os) const
  {
    if (root)
      root->printInorder(os);
  }
  void printPreorder(std::ostream &os) const
  {
    if (root)
      root->printPreorder(os);
  }
  void printPostorder(std::ostream &os) const
  {
    if (root)
      root->printPostorder(os);
  }
  std::vector<std::string> stepEvaluate() const
  {
    std::vector<std::string> steps;
    if (root)
      root->stepEvaluate(steps);
    return steps;
  }
  void destroy() { root.reset(); }
};