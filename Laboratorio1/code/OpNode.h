#ifndef OPNODE_H
#define OPNODE_H

#include <memory>
#include <stdexcept>

struct OpNode
{
  virtual ~OpNode() = default;
  virtual double eval() const = 0;
};

struct NumberNode : OpNode
{
  double value;
  NumberNode(double v) : value(v) {}
  double eval() const override { return value; }
};

struct BinaryNode : OpNode
{
  char op;
  std::unique_ptr<OpNode> left, right;
  BinaryNode(char o, std::unique_ptr<OpNode> l, std::unique_ptr<OpNode> r)
      : op(o), left(std::move(l)), right(std::move(r)) {}
  double eval() const override;
};

struct Operacion : OpNode
{
  virtual char simbolo() const = 0;
};

struct Suma : Operacion
{
  std::unique_ptr<OpNode> left, right;
  Suma(std::unique_ptr<OpNode> l, std::unique_ptr<OpNode> r)
      : left(std::move(l)), right(std::move(r)) {}
  double eval() const override { return left->eval() + right->eval(); }
  char simbolo() const override { return '+'; }
};

struct Resta : Operacion
{
  std::unique_ptr<OpNode> left, right;
  Resta(std::unique_ptr<OpNode> l, std::unique_ptr<OpNode> r)
      : left(std::move(l)), right(std::move(r)) {}
  double eval() const override { return left->eval() - right->eval(); }
  char simbolo() const override { return '-'; }
};

struct Multiplicacion : Operacion
{
  std::unique_ptr<OpNode> left, right;
  Multiplicacion(std::unique_ptr<OpNode> l, std::unique_ptr<OpNode> r)
      : left(std::move(l)), right(std::move(r)) {}
  double eval() const override { return left->eval() * right->eval(); }
  char simbolo() const override { return '*'; }
};

struct Division : Operacion
{
  std::unique_ptr<OpNode> left, right;
  Division(std::unique_ptr<OpNode> l, std::unique_ptr<OpNode> r)
      : left(std::move(l)), right(std::move(r)) {}
  double eval() const override
  {
    double R = right->eval();
    if (R == 0)
      throw std::runtime_error("División por cero");
    return left->eval() / R;
  }
  char simbolo() const override { return '/'; }
};

#endif