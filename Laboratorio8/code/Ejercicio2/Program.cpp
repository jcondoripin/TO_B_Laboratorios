#include <iostream>

using namespace std;

template <class T>
class Contenedor
{
  T elemento;

public:
  Contenedor(T args)
  {
    elemento = args;
  }
  T add() { return ++elemento; }
};

template <>
class Contenedor<char>
{
  char elemento;

public:
  Contenedor(char args)
  {
    elemento = args;
  }
  char uppercase()
  {
    if ((elemento >= 'a') && (elemento <= 'z'))
    {
      elemento += ('A' - 'a');
    }
    return elemento;
  }
};

int main()
{
  Contenedor<int> cint(5);
  Contenedor<char> cchar('t');
  cout << cint.add() << endl;
  cout << cchar.uppercase() << endl;
  return 0;
}