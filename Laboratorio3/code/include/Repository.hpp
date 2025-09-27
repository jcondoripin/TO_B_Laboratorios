#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include <vector>
#include <memory>
#include <string>
#include "Alumno.hpp"
#include "Profesor.hpp"
#include "Tarea.hpp"

class Repository
{
public:
  void guardarAlumnos(const std::vector<std::shared_ptr<Alumno>> &alumnos, const std::string &filename);
  std::vector<std::shared_ptr<Alumno>> cargarAlumnos(const std::string &filename, const std::vector<std::shared_ptr<Profesor>> &profesores);

  void guardarProfesores(const std::vector<std::shared_ptr<Profesor>> &profesores, const std::string &filename);
  std::vector<std::shared_ptr<Profesor>> cargarProfesores(const std::string &filename);

  void guardarTareas(const std::vector<std::shared_ptr<Tarea>> &tareas, const std::string &filename);
  std::vector<std::shared_ptr<Tarea>> cargarTareas(const std::string &filename, const std::vector<std::shared_ptr<Profesor>> &profesores);
};

#endif