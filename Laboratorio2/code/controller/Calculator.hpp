#pragma once

#include "Parser.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

class Calculator
{
private:
  std::vector<std::pair<std::string, std::string>> history;

public:
  double compute(const std::string &exprStr)
  {
    try
    {
      std::string cleaned;
      for (char c : exprStr)
      {
        if (!std::isspace(c))
          cleaned += c;
      }

      Parser parser(cleaned);
      auto root = parser.parse();

      ExpressionTree tree;
      tree.setRoot(std::move(root));

      double result = tree.evaluate();

      std::ostringstream oss;
      oss << std::fixed << std::setprecision(2) << result;
      std::string resStr = oss.str();

      history.emplace_back(exprStr, resStr);

      auto steps = tree.stepEvaluate();
      std::cout << "Steps:\n";
      for (const auto &step : steps)
      {
        std::cout << step << std::endl;
      }

      return result;
    }
    catch (const std::exception &e)
    {
      std::string error = "Error: " + std::string(e.what());
      history.emplace_back(exprStr, error);
      std::cout << error << std::endl;
      return std::numeric_limits<double>::quiet_NaN();
    }
  }

  void showHistory() const
  {
    std::cout << "History:\n";
    for (const auto &h : history)
    {
      std::cout << h.first << " = " << h.second << std::endl;
    }
  }

  void exportHistory(const std::string &filename) const
  {
    std::ofstream file(filename);
    if (!file)
    {
      std::cout << "Error opening file for export.\n";
      return;
    }
    for (const auto &h : history)
    {
      file << h.first << " = " << h.second << std::endl;
    }
    std::cout << "History exported to " << filename << std::endl;
  }

  void importAndCompute(const std::string &filename, const std::string &outputFilename)
  {
    std::ifstream file(filename);
    if (!file)
    {
      std::cout << "Input file not found.\n";
      return;
    }
    std::ofstream out(outputFilename);
    if (!out)
    {
      std::cout << "Error opening output file.\n";
      return;
    }
    std::string line;
    while (std::getline(file, line))
    {
      if (line.empty())
        continue;
      double res = compute(line);
      std::string resStr = std::isnan(res) ? history.back().second : std::to_string(res);
      out << line << " = " << resStr << std::endl;
    }
    out.close();
    std::cout << "Results exported to " << outputFilename << std::endl;
  }
};
