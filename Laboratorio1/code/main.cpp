#include <fstream>
#include <iostream>
#include <iomanip>
#include "InputProcessor.h"
#include "CalculatorCore.h"
#include "Historial.h"

using namespace std;

void procesarArchivo(InputProcessor &inp, CalculatorCore &core, Historial &hist)
{
  std::ifstream fin("operaciones.txt");
  std::ofstream fout("resultados.txt");
  if (!fin)
  {
    std::cerr << "No se pudo abrir operaciones.txt\n";
    return;
  }
  std::string linea;
  while (getline(fin, linea))
  {
    try
    {
      auto tokens = inp.tokenize(linea);
      double result = core.evaluateTokens(tokens);
      fout << linea << " = " << result << "\n";
      hist.agregar(linea, std::to_string(result));
    }
    catch (const std::exception &ex)
    {
      fout << linea << " -> ERROR: " << ex.what() << "\n";
      hist.agregar(linea, std::string("ERROR: ") + ex.what());
    }
  }
  std::cout << "Resultados guardados en resultados.txt\n";
}

int main()
{
  InputProcessor inp(6);
  CalculatorCore core;
  Historial hist;

  int opcion;
  std::string linea;

  do
  {
    cout << "\n=== MENU CALCULADORA ===\n";
    cout << "1. Ingresar operacion\n";
    cout << "2. Mostrar historial\n";
    cout << "3. Leer operaciones desde archivo\n";
    cout << "4. Salir\n";
    cout << "Seleccione opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion)
    {
    case 1:
      cout << "Ingrese operacion: ";
      getline(cin, linea);
      try
      {
        auto tokens = inp.tokenize(linea);
        double result = core.evaluateTokens(tokens);
        cout << linea << " = " << result << endl;
        hist.agregar(linea, to_string(result));
      }
      catch (const exception &ex)
      {
        cerr << "Error: " << ex.what() << endl;
        hist.agregar(linea, std::string("ERROR: ") + ex.what());
      }
      break;
    case 2:
      hist.mostrar();
      break;
    case 3:
      procesarArchivo(inp, core, hist);
      break;
    case 4:
      cout << "Saliendo...\n";
      break;
    default:
      cout << "Opcion invalida\n";
    }
  } while (opcion != 4);

  return 0;
}