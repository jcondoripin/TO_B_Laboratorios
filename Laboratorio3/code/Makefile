# File: Makefile
# Makefile para compilar el proyecto SchoolManagementSystem

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS =

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
EXECUTABLE = school_system

# Regla por defecto: compilar el ejecutable
all: $(BUILD_DIR) $(EXECUTABLE)

# Crear directorio build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linkear objetos para crear el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Compilar cada archivo fuente a objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Ejecutar el programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Regla para evitar conflictos con archivos llamados "clean" o "all"
.PHONY: all clean run