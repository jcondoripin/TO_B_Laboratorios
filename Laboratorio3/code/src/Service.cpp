#include "../include/Service.hpp"
#include <iostream>
#include <iomanip>

Service::Service()
{
  cargarDatos();
}

Service::~Service()
{
  guardarDatos();
}

void Service::registrarAlumno(const std::string &codigo, int grado, const std::string &nombres, const std::string &apellidos)
{
  if (!codigoAlumnoUnico(codigo))
  {
    std::cout << "Codigo de alumno ya existe." << std::endl;
    return;
  }
  if (!gradoValido(grado))
  {
    std::cout << "Grado invalido. Debe ser entre 1 y 6." << std::endl;
    return;
  }
  auto alumno = std::make_shared<Alumno>(codigo, grado, nombres, apellidos);
  alumnos.push_back(alumno);
  std::cout << "Alumno registrado exitosamente." << std::endl;
}

void Service::registrarProfesor(const std::string &nombres, const std::string &apellidos)
{
  auto profesor = std::make_shared<Profesor>(nombres, apellidos);
  profesores.push_back(profesor);
  std::cout << "Profesor registrado exitosamente." << std::endl;
}

void Service::registrarTarea(const std::string &codigoAlumno, const std::string &curso, const std::string &nombreProfesor, const std::string &fecha, bool entregada)
{
  size_t spacePos = nombreProfesor.find(' ');
  std::string nombres = nombreProfesor.substr(0, spacePos);
  std::string apellidos = nombreProfesor.substr(spacePos + 1);

  if (!profesorExiste(nombres, apellidos))
  {
    std::cout << "Profesor no existe." << std::endl;
    return;
  }
  auto prof = buscarProfesorPorNombre(nombres, apellidos);
  auto alumno = buscarAlumnoPorCodigo(codigoAlumno);
  if (!alumno)
  {
    std::cout << "Alumno no existe." << std::endl;
    return;
  }
  auto tarea = std::make_shared<Tarea>(curso, prof, fecha, entregada);
  alumno->agregarTarea(tarea);
  prof->agregarAlumno(alumno);
  tareas.push_back(tarea);
  std::cout << "Tarea registrada exitosamente." << std::endl;
}

std::shared_ptr<Alumno> Service::buscarAlumnoPorCodigo(const std::string &codigo) const
{
  for (const auto &alumno : alumnos)
  {
    if (alumno->getCodigo() == codigo)
    {
      return alumno;
    }
  }
  return nullptr;
}

std::shared_ptr<Profesor> Service::buscarProfesorPorNombre(const std::string &nombres, const std::string &apellidos) const
{
  for (const auto &prof : profesores)
  {
    if (prof->getNombres() == nombres && prof->getApellidos() == apellidos)
    {
      return prof;
    }
  }
  return nullptr;
}

std::vector<std::shared_ptr<Tarea>> Service::buscarTareasPorCurso(const std::string &curso) const
{
  std::vector<std::shared_ptr<Tarea>> result;
  for (const auto &tarea : tareas)
  {
    if (tarea->getCurso() == curso)
    {
      result.push_back(tarea);
    }
  }
  return result;
}

void Service::consultarTareasAlumno(const std::string &codigo)
{
  auto alumno = buscarAlumnoPorCodigo(codigo);
  if (!alumno)
  {
    std::cout << "Alumno no encontrado." << std::endl;
    return;
  }
  std::cout << "Tareas de " << alumno->getNombres() << " " << alumno->getApellidos() << ":" << std::endl;
  for (const auto &tarea : alumno->getTareas())
  {
    std::cout << "- Curso: " << tarea->getCurso() << ", Fecha: " << tarea->getFecha() << ", Entregada: " << (tarea->isEntregada() ? "Si" : "No") << std::endl;
  }
}

void Service::consultarAlumnosProfesor(const std::string &nombreProfesor)
{
  size_t spacePos = nombreProfesor.find(' ');
  std::string nombres = nombreProfesor.substr(0, spacePos);
  std::string apellidos = nombreProfesor.substr(spacePos + 1);
  auto prof = buscarProfesorPorNombre(nombres, apellidos);
  if (!prof)
  {
    std::cout << "Profesor no encontrado." << std::endl;
    return;
  }
  std::cout << "Alumnos de " << prof->getNombres() << " " << prof->getApellidos() << ":" << std::endl;
  for (const auto &alumno : prof->getAlumnos())
  {
    std::cout << "- " << alumno->getNombres() << " " << alumno->getApellidos() << " (Codigo: " << alumno->getCodigo() << ")" << std::endl;
  }
}

void Service::generarReportes()
{
  std::cout << "Reportes:" << std::endl;
  for (const auto &alumno : alumnos)
  {
    int entregadas = alumno->contarTareasEntregadas();
    int total = alumno->contarTareasTotales();
    double porcentaje = total > 0 ? (static_cast<double>(entregadas) / total) * 100 : 0;
    std::cout << "Alumno " << alumno->getNombres() << " " << alumno->getApellidos() << ": " << entregadas << " tareas entregadas, " << std::fixed << std::setprecision(2) << porcentaje << "%" << std::endl;
  }
  for (const auto &prof : profesores)
  {
    std::cout << "Profesor " << prof->getNombres() << " " << prof->getApellidos() << ": " << prof->contarAlumnos() << " alumnos" << std::endl;
  }
}

void Service::cargarDatos()
{
  profesores = repo.cargarProfesores("profesores.txt");
  alumnos = repo.cargarAlumnos("alumnos.txt", profesores);
  tareas = repo.cargarTareas("tareas.txt", profesores);
  for (const auto &alumno : alumnos)
  {
    for (const auto &tarea : alumno->getTareas())
    {
      auto prof = tarea->getProfesor();
      bool exists = false;
      for (const auto &a : prof->getAlumnos())
      {
        if (a->getCodigo() == alumno->getCodigo())
        {
          exists = true;
          break;
        }
      }
      if (!exists)
      {
        prof->agregarAlumno(alumno);
      }
    }
  }
}

void Service::guardarDatos()
{
  repo.guardarProfesores(profesores, "profesores.txt");
  repo.guardarAlumnos(alumnos, "alumnos.txt");
  repo.guardarTareas(tareas, "tareas.txt");
}

bool Service::codigoAlumnoUnico(const std::string &codigo) const
{
  return buscarAlumnoPorCodigo(codigo) == nullptr;
}

bool Service::gradoValido(int grado) const
{
  return grado >= 1 && grado <= 6;
}

bool Service::profesorExiste(const std::string &nombres, const std::string &apellidos) const
{
  return buscarProfesorPorNombre(nombres, apellidos) != nullptr;
}