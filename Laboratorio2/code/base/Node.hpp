#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Node
{
public:
  virtual ~Node() = default;
  virtual double evaluate() const = 0;
  virtual void printInorder(std::ostream &os) const = 0;
  virtual void printPreorder(std::ostream &os) const = 0;
  virtual void printPostorder(std::ostream &os) const = 0;
  virtual std::string toString() const = 0;
  virtual void stepEvaluate(std::vector<std::string> &steps) const = 0;
};