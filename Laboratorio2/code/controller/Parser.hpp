#pragma once
#include "../base/ExpressionTree.hpp"
#include "../core/NumberNode.hpp"
#include "../core/operations/SumNode.hpp"
#include "../core/operations/SubtractNode.hpp"
#include "../core/operations/MultiplyNode.hpp"
#include "../core/operations/DivideNode.hpp"
#include <string>
#include <cctype>
#include <stdexcept>
#include <memory>

class Parser
{
private:
  std::string expr;
  size_t pos;

  void skipSpaces()
  {
    while (pos < expr.size() && std::isspace(expr[pos]))
      ++pos;
  }

  double parseNumber()
  {
    std::string num;
    while (pos < expr.size() && (std::isdigit(expr[pos]) || expr[pos] == '.'))
    {
      num += expr[pos++];
    }
    if (num.empty())
      throw std::runtime_error("Invalid number");
    return std::stod(num);
  }

  std::unique_ptr<Node> parseAtom()
  {
    skipSpaces();
    if (pos >= expr.size())
      throw std::runtime_error("Unexpected end of expression");
    if (expr[pos] == '(')
    {
      ++pos;
      auto node = parseExpression();
      skipSpaces();
      if (pos >= expr.size() || expr[pos] != ')')
        throw std::runtime_error("Mismatched parentheses");
      ++pos;
      return node;
    }
    else if (std::isdigit(expr[pos]) || expr[pos] == '-')
    {
      bool neg = false;
      if (expr[pos] == '-')
      {
        neg = true;
        ++pos;
      }
      double val = parseNumber();
      if (neg)
        val = -val;
      return std::unique_ptr<Node>(new NumberNode(val));
    }
    else
    {
      throw std::runtime_error("Invalid atom at position " + std::to_string(pos));
    }
  }

  std::unique_ptr<Node> parseTerm()
  {
    auto left = parseAtom();
    skipSpaces();
    while (pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/'))
    {
      size_t opPos = pos;
      char op = expr[pos++];
      skipSpaces();
      auto right = parseAtom();
      skipSpaces();
      std::unique_ptr<Node> node;
      if (op == '*')
      {
        node = std::unique_ptr<Node>(new MultiplyNode(std::move(left), std::move(right)));
      }
      else
      {
        node = std::unique_ptr<Node>(new DivideNode(std::move(left), std::move(right)));
      }
      if (!static_cast<OperatorNode *>(node.get())->isValidInContext(expr, opPos))
      {
        throw std::runtime_error("Invalid context for operator " + std::string(1, op));
      }
      left = std::move(node);
    }
    return left;
  }

  std::unique_ptr<Node> parseExpression()
  {
    auto left = parseTerm();
    skipSpaces();
    while (pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-'))
    {
      size_t opPos = pos;
      char op = expr[pos++];
      skipSpaces();
      auto right = parseTerm();
      skipSpaces();
      std::unique_ptr<Node> node;
      if (op == '+')
      {
        node = std::unique_ptr<Node>(new SumNode(std::move(left), std::move(right)));
      }
      else
      {
        node = std::unique_ptr<Node>(new SubtractNode(std::move(left), std::move(right)));
      }
      if (!static_cast<OperatorNode *>(node.get())->isValidInContext(expr, opPos))
      {
        throw std::runtime_error("Invalid context for operator " + std::string(1, op));
      }
      left = std::move(node);
    }
    return left;
  }

public:
  Parser(const std::string &s) : expr(s), pos(0) {}
  std::unique_ptr<Node> parse()
  {
    skipSpaces();
    auto tree = parseExpression();
    skipSpaces();
    if (pos < expr.size())
      throw std::runtime_error("Extra characters after expression");
    return tree;
  }
};