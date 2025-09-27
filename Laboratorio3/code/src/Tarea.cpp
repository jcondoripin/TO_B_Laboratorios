#include "../include/Tarea.hpp"
#include "../include/Profesor.hpp"

Tarea::Tarea(const std::string &curso, std::shared_ptr<Profesor> profesor, const std::string &fecha, bool entregada)
    : curso(curso), profesor(profesor), fecha(fecha), entregada(entregada) {}

std::string Tarea::getCurso() const
{
  return curso;
}

std::shared_ptr<Profesor> Tarea::getProfesor() const
{
  return profesor;
}

std::string Tarea::getFecha() const
{
  return fecha;
}

bool Tarea::isEntregada() const
{
  return entregada;
}

void Tarea::setEntregada(bool entregada)
{
  this->entregada = entregada;
}