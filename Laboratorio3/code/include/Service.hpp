#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <vector>
#include <memory>
#include <string>
#include "Alumno.hpp"
#include "Profesor.hpp"
#include "Tarea.hpp"
#include "Repository.hpp"

class Service
{
public:
  Service();
  ~Service();

  void registrarAlumno(const std::string &codigo, int grado, const std::string &nombres, const std::string &apellidos);
  void registrarProfesor(const std::string &nombres, const std::string &apellidos);
  void registrarTarea(const std::string &codigoAlumno, const std::string &curso, const std::string &nombreProfesor, const std::string &fecha, bool entregada);

  std::shared_ptr<Alumno> buscarAlumnoPorCodigo(const std::string &codigo) const;
  std::shared_ptr<Profesor> buscarProfesorPorNombre(const std::string &nombres, const std::string &apellidos) const;
  std::vector<std::shared_ptr<Tarea>> buscarTareasPorCurso(const std::string &curso) const;

  void consultarTareasAlumno(const std::string &codigo);
  void consultarAlumnosProfesor(const std::string &nombreProfesor);
  void generarReportes();

  void cargarDatos();
  void guardarDatos();

private:
  std::vector<std::shared_ptr<Alumno>> alumnos;
  std::vector<std::shared_ptr<Profesor>> profesores;
  std::vector<std::shared_ptr<Tarea>> tareas;

  Repository repo;

  bool codigoAlumnoUnico(const std::string &codigo) const;
  bool gradoValido(int grado) const;
  bool profesorExiste(const std::string &nombres, const std::string &apellidos) const;
};

#endif