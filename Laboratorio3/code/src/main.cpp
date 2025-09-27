#include <iostream>
#include <string>
#include "../include/Service.hpp"

int main()
{
  Service service;
  int opcion;
  do
  {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Registrar alumno" << std::endl;
    std::cout << "2. Registrar profesor" << std::endl;
    std::cout << "3. Registrar tarea" << std::endl;
    std::cout << "4. Consultar tareas de un alumno" << std::endl;
    std::cout << "5. Consultar alumnos de un profesor" << std::endl;
    std::cout << "6. Generar reportes" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opcion;
    std::cin.ignore();

    if (opcion == 1)
    {
      std::string codigo, nombres, apellidos;
      int grado;
      std::cout << "Codigo: ";
      std::getline(std::cin, codigo);
      std::cout << "Grado (1-6): ";
      std::cin >> grado;
      std::cin.ignore();
      std::cout << "Nombres: ";
      std::getline(std::cin, nombres);
      std::cout << "Apellidos: ";
      std::getline(std::cin, apellidos);
      service.registrarAlumno(codigo, grado, nombres, apellidos);
    }
    else if (opcion == 2)
    {
      std::string nombres, apellidos;
      std::cout << "Nombres: ";
      std::getline(std::cin, nombres);
      std::cout << "Apellidos: ";
      std::getline(std::cin, apellidos);
      service.registrarProfesor(nombres, apellidos);
    }
    else if (opcion == 3)
    {
      std::string codigoAlumno, curso, nombreProfesor, fecha;
      bool entregada;
      std::cout << "Codigo alumno: ";
      std::getline(std::cin, codigoAlumno);
      std::cout << "Curso: ";
      std::getline(std::cin, curso);
      std::cout << "Nombre profesor (nombres apellidos): ";
      std::getline(std::cin, nombreProfesor);
      std::cout << "Fecha: ";
      std::getline(std::cin, fecha);
      std::cout << "Entregada (1/0): ";
      std::cin >> entregada;
      std::cin.ignore();
      service.registrarTarea(codigoAlumno, curso, nombreProfesor, fecha, entregada);
    }
    else if (opcion == 4)
    {
      std::string codigo;
      std::cout << "Codigo alumno: ";
      std::getline(std::cin, codigo);
      service.consultarTareasAlumno(codigo);
    }
    else if (opcion == 5)
    {
      std::string nombreProfesor;
      std::cout << "Nombre profesor (nombres apellidos): ";
      std::getline(std::cin, nombreProfesor);
      service.consultarAlumnosProfesor(nombreProfesor);
    }
    else if (opcion == 6)
    {
      service.generarReportes();
    }
  } while (opcion != 0);

  return 0;
}