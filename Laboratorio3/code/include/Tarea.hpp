#ifndef TAREA_HPP
#define TAREA_HPP

#include <string>
#include <memory>

class Profesor;
class Alumno;

class Tarea
{
public:
  Tarea(const std::string &curso, std::shared_ptr<Profesor> profesor, const std::string &fecha, bool entregada);

  std::string getCurso() const;
  std::shared_ptr<Profesor> getProfesor() const;
  std::string getFecha() const;
  bool isEntregada() const;
  void setEntregada(bool entregada);

private:
  std::string curso;
  std::shared_ptr<Profesor> profesor;
  std::string fecha;
  bool entregada;
};

#endif 