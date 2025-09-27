#include "../include/Service.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

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
    std::cout << "Error: El codigo de alumno ya existe." << std::endl;
    return;
  }
  if (!gradoValido(grado))
  {
    std::cout << "Error: Grado invalido. Debe ser entre 1 y 6." << std::endl;
    return;
  }
  auto alumno = std::make_shared<Alumno>(codigo, grado, nombres, apellidos);
  alumnos.push_back(alumno);
  std::cout << "Alumno registrado exitosamente: " << nombres << " " << apellidos << std::endl;
}

void Service::registrarProfesor(const std::string &nombres, const std::string &apellidos)
{
  auto profesor = std::make_shared<Profesor>(nombres, apellidos);
  profesores.push_back(profesor);
  std::cout << "Profesor registrado exitosamente: " << nombres << " " << apellidos << std::endl;
}

void Service::registrarTarea(const std::string &codigoAlumno, const std::string &curso, const std::string &profesorNombres, const std::string &profesorApellidos, const std::string &fecha, bool entregada)
{
  if (!profesorExiste(profesorNombres, profesorApellidos))
  {
    std::cout << "Error: Profesor '" << profesorNombres << " " << profesorApellidos << "' no existe." << std::endl;
    return;
  }
  auto prof = buscarProfesorPorNombre(profesorNombres, profesorApellidos);
  auto alumno = buscarAlumnoPorCodigo(codigoAlumno);
  if (!alumno)
  {
    std::cout << "Error: Alumno con codigo '" << codigoAlumno << "' no existe." << std::endl;
    return;
  }
  auto tarea = std::make_shared<Tarea>(curso, prof, fecha, entregada);
  alumno->agregarTarea(tarea);
  bool alumnoExists = false;
  for (const auto &a : prof->getAlumnos())
  {
    if (a->getCodigo() == alumno->getCodigo())
    {
      alumnoExists = true;
      break;
    }
  }
  if (!alumnoExists)
  {
    prof->agregarAlumno(alumno);
  }
  tareas.push_back(tarea);
  std::cout << "Tarea registrada exitosamente para el curso " << curso << "." << std::endl;
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
  std::string nombresLower = nombres;
  std::string apellidosLower = apellidos;
  std::transform(nombresLower.begin(), nombresLower.end(), nombresLower.begin(), [](unsigned char c)
                 { return std::tolower(c); });
  std::transform(apellidosLower.begin(), apellidosLower.end(), apellidosLower.begin(), [](unsigned char c)
                 { return std::tolower(c); });

  for (const auto &prof : profesores)
  {
    std::string profNombresLower = prof->getNombres();
    std::string profApellidosLower = prof->getApellidos();
    std::transform(profNombresLower.begin(), profNombresLower.end(), profNombresLower.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    std::transform(profApellidosLower.begin(), profApellidosLower.end(), profApellidosLower.begin(), [](unsigned char c)
                   { return std::tolower(c); });

    if (profNombresLower == nombresLower && profApellidosLower == apellidosLower)
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
    std::cout << "Error: Alumno con codigo '" << codigo << "' no encontrado." << std::endl;
    return;
  }
  std::cout << "\nTareas de " << alumno->getNombres() << " " << alumno->getApellidos() << " (Codigo: " << codigo << "):" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  if (alumno->getTareas().empty())
  {
    std::cout << "No hay tareas asignadas." << std::endl;
  }
  else
  {
    for (const auto &tarea : alumno->getTareas())
    {
      std::cout << "Curso: " << tarea->getCurso()
                << ", Fecha: " << tarea->getFecha()
                << ", Entregada: " << (tarea->isEntregada() ? "Si" : "No") << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}

void Service::consultarAlumnosProfesor(const std::string &nombreProfesor)
{
  std::string trimmedNombreProfesor = nombreProfesor;
  trimmedNombreProfesor.erase(trimmedNombreProfesor.begin(), std::find_if(trimmedNombreProfesor.begin(), trimmedNombreProfesor.end(), [](unsigned char c)
                                                                          { return !std::isspace(c); }));
  trimmedNombreProfesor.erase(std::find_if(trimmedNombreProfesor.rbegin(), trimmedNombreProfesor.rend(), [](unsigned char c)
                                           { return !std::isspace(c); })
                                  .base(),
                              trimmedNombreProfesor.end());

  size_t lastSpace = trimmedNombreProfesor.rfind(' ');
  if (lastSpace == std::string::npos)
  {
    std::cout << "Error: Formato de nombre de profesor invalido. Use 'nombres apellidos'." << std::endl;
    return;
  }
  std::string nombres = trimmedNombreProfesor.substr(0, lastSpace);
  std::string apellidos = trimmedNombreProfesor.substr(lastSpace + 1);

  auto prof = buscarProfesorPorNombre(nombres, apellidos);
  if (!prof)
  {
    std::cout << "Error: Profesor '" << nombres << " " << apellidos << "' no encontrado." << std::endl;
    return;
  }
  std::cout << "\nAlumnos de " << prof->getNombres() << " " << prof->getApellidos() << ":" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  if (prof->getAlumnos().empty())
  {
    std::cout << "No hay alumnos asignados." << std::endl;
  }
  else
  {
    for (const auto &alumno : prof->getAlumnos())
    {
      std::cout << "Codigo: " << alumno->getCodigo() << ", Nombre: " << alumno->getNombres() << " " << alumno->getApellidos() << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}

void Service::generarReportes()
{
  std::cout << "\nReportes:" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "Tareas por alumno:" << std::endl;
  if (alumnos.empty())
  {
    std::cout << "No hay alumnos registrados." << std::endl;
  }
  else
  {
    for (const auto &alumno : alumnos)
    {
      int entregadas = alumno->contarTareasEntregadas();
      int total = alumno->contarTareasTotales();
      double porcentaje = total > 0 ? (static_cast<double>(entregadas) / total) * 100 : 0;
      std::cout << "Alumno: " << alumno->getNombres() << " " << alumno->getApellidos()
                << ", Codigo: " << alumno->getCodigo()
                << ", Tareas entregadas: " << entregadas << "/" << total
                << ", Porcentaje: " << std::fixed << std::setprecision(2) << porcentaje << "%" << std::endl;
    }
  }
  std::cout << "\nAlumnos por profesor:" << std::endl;
  if (profesores.empty())
  {
    std::cout << "No hay profesores registrados." << std::endl;
  }
  else
  {
    for (const auto &prof : profesores)
    {
      std::cout << "Profesor: " << prof->getNombres() << " " << prof->getApellidos()
                << ", Alumnos a cargo: " << prof->contarAlumnos() << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}

void Service::listarAlumnos() const
{
  std::cout << "\nLista de Alumnos:" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  if (alumnos.empty())
  {
    std::cout << "No hay alumnos registrados." << std::endl;
  }
  else
  {
    for (size_t i = 0; i < alumnos.size(); ++i)
    {
      std::cout << "ID: " << i + 1 << ", Codigo: " << alumnos[i]->getCodigo()
                << ", Nombre: " << alumnos[i]->getNombres() << " " << alumnos[i]->getApellidos()
                << ", Grado: " << alumnos[i]->getGrado() << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}

void Service::listarProfesores() const
{
  std::cout << "\nLista de Profesores:" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  if (profesores.empty())
  {
    std::cout << "No hay profesores registrados." << std::endl;
  }
  else
  {
    for (size_t i = 0; i < profesores.size(); ++i)
    {
      std::cout << "ID: " << i + 1 << ", Nombre: " << profesores[i]->getNombres() << " " << profesores[i]->getApellidos() << std::endl;
    }
  }
  std::cout << "----------------------------------------" << std::endl;
}

const std::vector<std::shared_ptr<Alumno>> &Service::getAlumnos() const
{
  return alumnos;
}

const std::vector<std::shared_ptr<Profesor>> &Service::getProfesores() const
{
  return profesores;
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