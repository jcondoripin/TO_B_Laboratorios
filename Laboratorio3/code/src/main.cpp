#include <iostream>
#include <string>
#include <limits>
#include "../include/Service.hpp"

// Funcion para limpiar el buffer de entrada
void clearInputBuffer()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
  Service service;
  int opcion;
  do
  {
    std::cout << "\n=== Sistema de Gestion Escolar ===" << std::endl;
    std::cout << "1. Registrar alumno" << std::endl;
    std::cout << "2. Registrar profesor" << std::endl;
    std::cout << "3. Registrar tarea" << std::endl;
    std::cout << "4. Consultar tareas de un alumno" << std::endl;
    std::cout << "5. Consultar alumnos de un profesor" << std::endl;
    std::cout << "6. Generar reportes" << std::endl;
    std::cout << "7. Listar datos" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;
    clearInputBuffer();

    if (opcion == 1)
    {
      std::string codigo, nombres, apellidos;
      int grado;
      std::cout << "\n--- Registrar Alumno ---" << std::endl;
      std::cout << "Ingrese codigo unico: ";
      std::getline(std::cin, codigo);
      std::cout << "Ingrese grado (1-6): ";
      std::cin >> grado;
      clearInputBuffer();
      std::cout << "Ingrese nombres: ";
      std::getline(std::cin, nombres);
      std::cout << "Ingrese apellidos: ";
      std::getline(std::cin, apellidos);
      service.registrarAlumno(codigo, grado, nombres, apellidos);
    }
    else if (opcion == 2)
    {
      std::string nombres, apellidos;
      std::cout << "\n--- Registrar Profesor ---" << std::endl;
      std::cout << "Ingrese nombres: ";
      std::getline(std::cin, nombres);
      std::cout << "Ingrese apellidos: ";
      std::getline(std::cin, apellidos);
      service.registrarProfesor(nombres, apellidos);
    }
    else if (opcion == 3)
    {
      std::cout << "\n--- Registrar Tarea ---" << std::endl;
      // Mostrar alumnos
      service.listarAlumnos();
      const auto &alumnos = service.getAlumnos();
      if (alumnos.empty())
      {
        std::cout << "No hay alumnos registrados. Registre un alumno primero." << std::endl;
        continue;
      }
      std::cout << "Ingrese ID del alumno (0 para cancelar): ";
      int alumnoId;
      std::cin >> alumnoId;
      clearInputBuffer();
      if (alumnoId == 0)
      {
        std::cout << "Operacion cancelada." << std::endl;
        continue;
      }
      if (alumnoId < 1 || alumnoId > static_cast<int>(alumnos.size()))
      {
        std::cout << "Error: ID de alumno invalido." << std::endl;
        continue;
      }
      std::string codigoAlumno = alumnos[alumnoId - 1]->getCodigo();
      // Mostrar profesores
      service.listarProfesores();
      const auto &profesores = service.getProfesores();
      if (profesores.empty())
      {
        std::cout << "No hay profesores registrados. Registre un profesor primero." << std::endl;
        continue;
      }
      std::cout << "Ingrese ID del profesor (0 para cancelar): ";
      int profesorId;
      std::cin >> profesorId;
      clearInputBuffer();
      if (profesorId == 0)
      {
        std::cout << "Operacion cancelada." << std::endl;
        continue;
      }
      if (profesorId < 1 || profesorId > static_cast<int>(profesores.size()))
      {
        std::cout << "Error: ID de profesor invalido." << std::endl;
        continue;
      }
      std::string profesorNombres = profesores[profesorId - 1]->getNombres();
      std::string profesorApellidos = profesores[profesorId - 1]->getApellidos();
      std::string curso, fecha;
      bool entregada;
      std::cout << "Ingrese curso: ";
      std::getline(std::cin, curso);
      std::cout << "Ingrese fecha (DD-MM-YYYY): ";
      std::getline(std::cin, fecha);
      std::cout << "Entregada (1 para Si, 0 para No): ";
      std::cin >> entregada;
      clearInputBuffer();
      service.registrarTarea(codigoAlumno, curso, profesorNombres, profesorApellidos, fecha, entregada);
    }
    else if (opcion == 4)
    {
      std::cout << "\n--- Consultar Tareas de Alumno ---" << std::endl;
      service.listarAlumnos();
      const auto &alumnos = service.getAlumnos();
      if (alumnos.empty())
      {
        std::cout << "No hay alumnos registrados." << std::endl;
        continue;
      }
      std::cout << "Ingrese ID del alumno (0 para cancelar): ";
      int alumnoId;
      std::cin >> alumnoId;
      clearInputBuffer();
      if (alumnoId == 0)
      {
        std::cout << "Operacion cancelada." << std::endl;
        continue;
      }
      if (alumnoId < 1 || alumnoId > static_cast<int>(alumnos.size()))
      {
        std::cout << "Error: ID de alumno invalido." << std::endl;
        continue;
      }
      std::string codigo = alumnos[alumnoId - 1]->getCodigo();
      service.consultarTareasAlumno(codigo);
    }
    else if (opcion == 5)
    {
      std::cout << "\n--- Consultar Alumnos de Profesor ---" << std::endl;
      service.listarProfesores();
      const auto &profesores = service.getProfesores();
      if (profesores.empty())
      {
        std::cout << "No hay profesores registrados." << std::endl;
        continue;
      }
      std::cout << "Ingrese ID del profesor (0 para cancelar): ";
      int profesorId;
      std::cin >> profesorId;
      clearInputBuffer();
      if (profesorId == 0)
      {
        std::cout << "Operacion cancelada." << std::endl;
        continue;
      }
      if (profesorId < 1 || profesorId > static_cast<int>(profesores.size()))
      {
        std::cout << "Error: ID de profesor invalido." << std::endl;
        continue;
      }
      std::string nombreProfesor = profesores[profesorId - 1]->getNombres() + " " + profesores[profesorId - 1]->getApellidos();
      service.consultarAlumnosProfesor(nombreProfesor);
    }
    else if (opcion == 6)
    {
      std::cout << "\n--- Generar Reportes ---" << std::endl;
      service.generarReportes();
    }
    else if (opcion == 7)
    {
      int subOpcion;
      do
      {
        std::cout << "\n=== Listar Datos ===" << std::endl;
        std::cout << "1. Listar alumnos" << std::endl;
        std::cout << "2. Listar profesores" << std::endl;
        std::cout << "0. Volver al menu principal" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> subOpcion;
        clearInputBuffer();
        if (subOpcion == 1)
        {
          service.listarAlumnos();
        }
        else if (subOpcion == 2)
        {
          service.listarProfesores();
        }
        else if (subOpcion != 0)
        {
          std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
        }
      } while (subOpcion != 0);
    }
    else if (opcion != 0)
    {
      std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
    }
  } while (opcion != 0);

  std::cout << "Saliendo del sistema. Datos guardados." << std::endl;
  return 0;
}