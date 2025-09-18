#pragma once
#include "../controller/Calculator.hpp"
#include <string>
#include <iostream>

class Menu
{
public:
  static void run(Calculator &calc)
  {
    std::string input;
    while (true)
    {
      std::cout << "\n--- Calculator Menu ---\n";
      std::cout << "1. Compute expression (e.g., 1+2*3-4 or (1+2)*3)\n";
      std::cout << "2. Show history\n";
      std::cout << "3. Export history to file\n";
      std::cout << "4. Import from file and compute\n";
      std::cout << "5. Exit\n";
      std::cout << "Choice: ";
      std::getline(std::cin, input);
      if (input == "1")
      {
        std::cout << "Enter expression: ";
        std::getline(std::cin, input);
        double res = calc.compute(input);
        std::cout << "Result: " << (std::isnan(res) ? "Error" : std::to_string(res)) << std::endl;
      }
      else if (input == "2")
      {
        calc.showHistory();
      }
      else if (input == "3")
      {
        std::cout << "Export filename: ";
        std::getline(std::cin, input);
        calc.exportHistory(input);
      }
      else if (input == "4")
      {
        std::string inFile, outFile;
        std::cout << "Input filename: ";
        std::getline(std::cin, inFile);
        std::cout << "Output filename: ";
        std::getline(std::cin, outFile);
        calc.importAndCompute(inFile, outFile);
      }
      else if (input == "5")
      {
        break;
      }
      else
      {
        std::cout << "Invalid choice.\n";
      }
    }
    calc.showHistory();
  }
};