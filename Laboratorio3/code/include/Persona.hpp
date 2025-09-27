#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>

class Persona
{
public:
  Persona(const std::string &nombres, const std::string &apellidos);
  virtual ~Persona() = default;

  std::string getNombres() const;
  std::string getApellidos() const;

private:
  std::string nombres;
  std::string apellidos;
};

#endif