#ifndef ALUMNO_HPP
#define ALUMNO_HPP

#include "Persona.hpp"
#include <string>
#include <vector>
#include <memory>

class Tarea;

class Alumno : public Persona
{
public:
  Alumno(const std::string &codigo, int grado, const std::string &nombres, const std::string &apellidos);

  std::string getCodigo() const;
  int getGrado() const;
  void agregarTarea(std::shared_ptr<Tarea> tarea);
  std::vector<std::shared_ptr<Tarea>> getTareas() const;
  int contarTareasEntregadas() const;
  int contarTareasTotales() const;

private:
  std::string codigo;
  int grado;
  std::vector<std::shared_ptr<Tarea>> tareas;
};

#endif