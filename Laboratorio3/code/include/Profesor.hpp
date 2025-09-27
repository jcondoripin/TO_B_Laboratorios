#ifndef PROFESOR_HPP
#define PROFESOR_HPP

#include "Persona.hpp"
#include <string>
#include <vector>
#include <memory>

class Alumno;

class Profesor : public Persona
{
public:
  Profesor(const std::string &nombres, const std::string &apellidos);

  void agregarAlumno(std::shared_ptr<Alumno> alumno);
  std::vector<std::shared_ptr<Alumno>> getAlumnos() const;
  int contarAlumnos() const;

private:
  std::vector<std::shared_ptr<Alumno>> alumnos;
};

#endif