# Calculadora Avanzada en C++

## Descripción

Este proyecto implementa una calculadora avanzada en C++ utilizando una arquitectura orientada a objetos y limpia. El sistema está diseñado para procesar expresiones matemáticas complejas, respetando la precedencia de operadores y manejando errores de manera robusta. Se basa en un árbol binario de expresiones (Expression Tree) para evaluar operaciones aritméticas básicas (+, -, *, /) y próximamente unarias (como sqrt). Incluye funcionalidades como historial de operaciones, importación y exportación de expresiones desde archivos de texto, y un menú interactivo para la interacción con el usuario.

El diseño promueve la extensibilidad: se puede agregar nuevos operadores binarios o unarios sin alterar el núcleo del sistema. Se utiliza manejo dinámico de memoria con punteros inteligentes (std::unique_ptr) para evitar fugas, y validaciones específicas por operador para garantizar la integridad sintáctica de las expresiones.

El proyecto está organizado en directorios modulares:
- **base/**: Clases base y utilidades fundamentales (e.g., Node, ExpressionTree).
- **core/**: Clases de operadores y nodos (e.g., SumNode, SqrtNode).
- **controller/**: Lógica de control y parsing (e.g., Calculator, Parser).
- **interface/**: Interfaz de usuario (e.g., Menu).
- **testing/**: Pruebas unitarias básicas.

## Características Principales

- Evaluación de expresiones con precedencia de operadores (e.g., 2+3*4 = 14).
- Soporte para paréntesis y números negativos (e.g., (1+2)*3, -2+5).
- Operadores binarios: suma (+), resta (-), multiplicación (*), división (/ con validación de división por cero).
- Validación contextual por operador (e.g., no permite /2 al inicio o 1//2).
- Historial de operaciones con resultados, incluyendo errores como texto.
- Importación de expresiones desde archivos .txt y generación de un archivo de resultados.
- Exportación del historial a archivo .txt.
- Evaluación paso a paso de expresiones complejas.
- Pruebas unitarias para expresiones válidas e inválidas.

## Requisitos

- Compilador C++11 o superior (e.g., g++).
- Bibliotecas estándar de C++ (no se requieren dependencias externas).

## Compilación e Instalación

### Compilación Manual (sin Makefile)

Para compilar manualmente el programa principal:

```bash
g++ -std=c++11 main.cpp -o program
```

Para compilar las pruebas:

```bash
g++ -std=c++11 test.cpp -o testing
```

## Ejecución

### Programa Principal

Ejecute el programa con:

```bash
./calc
```

Se abrirá un menú interactivo con las siguientes opciones:
1. Computar una expresión (e.g., 1+2*3-4 or (1+2)*3).
2. Mostrar historial.
3. Exportar historial a archivo.
4. Importar desde archivo y computar.
5. Salir.

Al finalizar, se muestra el historial completo.

### Pruebas

Ejecute las pruebas con:

```bash
./testing
```

Esto ejecuta pruebas para expresiones válidas e inválidas, mostrando un resumen de resultados.

## Uso y Ejemplos

### Ejemplos de Expresiones Válidas

- **Suma básica**: `1+2` → Resultado: 3.00
- **Precedencia**: `2+3*4` → Resultado: 14.00 (multiplicación primero)
- **Paréntesis**: `(1+2)*3` → Resultado: 9.00
- **Número negativo**: `-2+5` → Resultado: 3.00
- **División**: `6/2` → Resultado: 3.00

Para cada expresión, el sistema muestra pasos de evaluación (e.g., para `2+3*4`):
- Steps:
- 3 * 4 = 12
- 2 + 12 = 14

### Ejemplos de Expresiones Inválidas

- **División por cero**: `1/0` → Error: Division by zero
- **Contexto inválido**: `1//2` → Error: Invalid context for operator /
- **Operador inicial**: `+2` → Error: Invalid context for operator +
- **Paréntesis desbalanceados**: `(1+2` → Error: Mismatched parentheses

### Historial y Archivos

- El historial se almacena automáticamente y se muestra en la opción 2 o al salir.
- **Exportar**: Ingrese un nombre de archivo (e.g., `historial.txt`) en la opción 3.
- **Importar**: Proporcione un archivo de entrada (e.g., `expresiones.txt` con una expresión por línea) y un archivo de salida (e.g., `resultados.txt`). Genera resultados con errores indicados.

Ejemplo de archivo de entrada (`expresiones.txt`):
```
1+2
1/0
```

Archivo de salida (`resultados.txt`):
```
1+2 = 3
1/0 = Error
```

## Estructura del Proyecto

- **base/**: Clases abstractas y árboles de expresiones.
- **core/**: Implementaciones de nodos y operadores (binarios y próximamente unarios).
- **controller/**: Parser y calculadora principal.
- **interface/**: Menú interactivo.
- **testing/**: Pruebas unitarias.
- **main.cpp**: Punto de entrada.
- **Makefile**: Automatización de compilación.

## Contribuciones y Extensiones

Para agregar nuevos operadores:
1. Cree una clase en `core/` heredando de `OperatorNode` (binarios) o `UnaryOperatorNode` (unarios).
2. Implemente `evaluate`, `isValidInContext`, y métodos de impresión.
3. Actualice `controller/Parser.hpp` para reconocer el operador en `parseAtom` o `parseTerm`.
4. Agregue pruebas en `testing/TestCalculator.cpp`.
5. Incluya el nuevo `.cpp` en el Makefile si aplica.

Este proyecto es ideal para entornos educativos o prototipos, demostrando principios de diseño como herencia, polimorfismo y manejo de excepciones.

## Licencia

Proyecto de código abierto bajo licencia MIT (o especifique según preferencia). Para más detalles, contacte al autor.