#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
#include <vector>
#include <iostream>

class Historial
{
private:
  std::vector<std::pair<std::string, std::string>> registros;

public:
  void agregar(const std::string &expr, const std::string &res)
  {
    registros.emplace_back(expr, res);
  }

  void mostrar() const
  {
    std::cout << "\n=== HISTORIAL DE OPERACIONES ===\n";
    for (const auto &r : registros)
    {
      std::cout << r.first << " = " << r.second << "\n";
    }
  }
};

#endif
