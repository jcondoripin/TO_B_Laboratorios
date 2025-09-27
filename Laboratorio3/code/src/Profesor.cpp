#include "../include/Profesor.hpp"
#include "../include/Alumno.hpp"

Profesor::Profesor(const std::string &nombres, const std::string &apellidos)
    : Persona(nombres, apellidos) {}

void Profesor::agregarAlumno(std::shared_ptr<Alumno> alumno)
{
  alumnos.push_back(alumno);
}

std::vector<std::shared_ptr<Alumno>> Profesor::getAlumnos() const
{
  return alumnos;
}

int Profesor::contarAlumnos() const
{
  return static_cast<int>(alumnos.size());
}