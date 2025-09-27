#include "../include/Alumno.hpp"
#include "../include/Tarea.hpp"

Alumno::Alumno(const std::string &codigo, int grado, const std::string &nombres, const std::string &apellidos)
    : Persona(nombres, apellidos), codigo(codigo), grado(grado) {}

std::string Alumno::getCodigo() const
{
  return codigo;
}

int Alumno::getGrado() const
{
  return grado;
}

void Alumno::agregarTarea(std::shared_ptr<Tarea> tarea)
{
  tareas.push_back(tarea);
}

std::vector<std::shared_ptr<Tarea>> Alumno::getTareas() const
{
  return tareas;
}

int Alumno::contarTareasEntregadas() const
{
  int count = 0;
  for (const auto &tarea : tareas)
  {
    if (tarea->isEntregada())
    {
      ++count;
    }
  }
  return count;
}

int Alumno::contarTareasTotales() const
{
  return static_cast<int>(tareas.size());
}