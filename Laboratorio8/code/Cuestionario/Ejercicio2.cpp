#include <iostream>
#include <string>

template <typename T>
class Box
{
  T value;

public:
  explicit Box(T v) : value(v) {}

private:
  friend bool operator==(const Box &a, const Box &b)
  {
    return a.value == b.value;
  }

  friend std::ostream &operator<<(std::ostream &os, const Box &b)
  {
    os << b.value;
    return os;
  }
};

int main()
{
  Box<int> a(10), b(10);
  if (a == b)
    std::cout << "Iguales: " << a << '\n';
  Box<std::string> s("hola");
  std::cout << "Contenido: " << s << '\n';
  return 0;
}
