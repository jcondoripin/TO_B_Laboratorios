#include "../include/Repository.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void Repository::guardarAlumnos(const std::vector<std::shared_ptr<Alumno>> &alumnos, const std::string &filename)
{
  std::ofstream file(filename);
  if (!file)
  {
    std::cerr << "Error al abrir " << filename << std::endl;
    return;
  }
  for (const auto &alumno : alumnos)
  {
    file << alumno->getCodigo() << "," << alumno->getGrado() << "," << alumno->getNombres() << "," << alumno->getApellidos();
    for (const auto &tarea : alumno->getTareas())
    {
      file << "," << tarea->getCurso() << "," << tarea->getProfesor()->getNombres() << " " << tarea->getProfesor()->getApellidos() << "," << tarea->getFecha() << "," << tarea->isEntregada();
    }
    file << std::endl;
  }
}

std::vector<std::shared_ptr<Alumno>> Repository::cargarAlumnos(const std::string &filename, const std::vector<std::shared_ptr<Profesor>> &profesores)
{
  std::vector<std::shared_ptr<Alumno>> alumnos;
  std::ifstream file(filename);
  if (!file)
    return alumnos;

  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, ','))
    {
      parts.push_back(token);
    }
    if (parts.size() < 4)
      continue;

    auto alumno = std::make_shared<Alumno>(parts[0], std::stoi(parts[1]), parts[2], parts[3]);
    // Cargar tareas si hay mas partes (cada tarea: curso, prof full name, fecha, entregada)
    for (size_t i = 4; i < parts.size(); i += 4)
    {
      if (i + 3 >= parts.size())
        break;
      std::string profFullName = parts[i + 1];
      // Buscar profesor por nombre completo (simplificado)
      std::shared_ptr<Profesor> prof;
      for (const auto &p : profesores)
      {
        if (p->getNombres() + " " + p->getApellidos() == profFullName)
        {
          prof = p;
          break;
        }
      }
      if (prof)
      {
        auto tarea = std::make_shared<Tarea>(parts[i], prof, parts[i + 2], parts[i + 3] == "1");
        alumno->agregarTarea(tarea);
      }
    }
    alumnos.push_back(alumno);
  }
  return alumnos;
}

void Repository::guardarProfesores(const std::vector<std::shared_ptr<Profesor>> &profesores, const std::string &filename)
{
  std::ofstream file(filename);
  if (!file)
  {
    std::cerr << "Error al abrir " << filename << std::endl;
    return;
  }
  for (const auto &prof : profesores)
  {
    file << prof->getNombres() << "," << prof->getApellidos();
    for (const auto &alumno : prof->getAlumnos())
    {
      file << "," << alumno->getCodigo();
    }
    file << std::endl;
  }
}

std::vector<std::shared_ptr<Profesor>> Repository::cargarProfesores(const std::string &filename)
{
  std::vector<std::shared_ptr<Profesor>> profesores;
  std::ifstream file(filename);
  if (!file)
    return profesores;

  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, ','))
    {
      parts.push_back(token);
    }
    if (parts.size() < 2)
      continue;

    auto prof = std::make_shared<Profesor>(parts[0], parts[1]);
    // Alumnos se agregaran despues, cuando carguemos alumnos
    profesores.push_back(prof);
  }
  return profesores;
}

void Repository::guardarTareas(const std::vector<std::shared_ptr<Tarea>> &tareas, const std::string &filename)
{
  std::ofstream file(filename);
  if (!file)
  {
    std::cerr << "Error al abrir " << filename << std::endl;
    return;
  }
  for (const auto &tarea : tareas)
  {
    file << tarea->getCurso() << "," << tarea->getProfesor()->getNombres() << " " << tarea->getProfesor()->getApellidos() << "," << tarea->getFecha() << "," << tarea->isEntregada() << std::endl;
  }
}

std::vector<std::shared_ptr<Tarea>> Repository::cargarTareas(const std::string &filename, const std::vector<std::shared_ptr<Profesor>> &profesores)
{
  std::vector<std::shared_ptr<Tarea>> tareas;
  std::ifstream file(filename);
  if (!file)
    return tareas;

  std::string line;
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(ss, token, ','))
    {
      parts.push_back(token);
    }
    if (parts.size() < 4)
      continue;

    std::string profFullName = parts[1];
    std::shared_ptr<Profesor> prof;
    for (const auto &p : profesores)
    {
      if (p->getNombres() + " " + p->getApellidos() == profFullName)
      {
        prof = p;
        break;
      }
    }
    if (prof)
    {
      auto tarea = std::make_shared<Tarea>(parts[0], prof, parts[2], parts[3] == "1");
      tareas.push_back(tarea);
    }
  }
  return tareas;
}