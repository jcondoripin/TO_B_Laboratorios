#include "../include/Persona.hpp"

Persona::Persona(const std::string &nombres, const std::string &apellidos)
    : nombres(nombres), apellidos(apellidos) {}

std::string Persona::getNombres() const
{
  return nombres;
}

std::string Persona::getApellidos() const
{
  return apellidos;
}