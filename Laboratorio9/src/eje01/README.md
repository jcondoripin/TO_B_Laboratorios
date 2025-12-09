# README.md - Ejercicio 01: Implementación Básica del Singleton

¡Bienvenido a este ejercicio introductorio al patrón Singleton! Aquí creamos una clase `Configuracion` que actúa como un gestor único de ajustes globales, como el idioma y la zona horaria. Esto asegura que toda la aplicación use la misma instancia, evitando duplicados y manteniendo la consistencia. El constructor privado y el método `getInstancia` controlan el acceso, mientras que funciones como `mostrarConfiguracion` permiten ver los valores actuales de forma sencilla.

### Código Fuente
**Configuracion.java**
```java
public class Configuracion {
    private static Configuracion instancia;
    private String idioma;
    private String zonaHoraria;

    private Configuracion() {
        this.idioma = "es"; // Valor por defecto
        this.zonaHoraria = "America/Lima"; // Valor por defecto
    }

    public static Configuracion getInstancia() {
        if (instancia == null) {
            instancia = new Configuracion();
        }
        return instancia;
    }

    public void setIdioma(String idioma) {
        this.idioma = idioma;
    }

    public void setZonaHoraria(String zonaHoraria) {
        this.zonaHoraria = zonaHoraria;
    }

    public void mostrarConfiguracion() {
        System.out.println("Idioma: " + idioma);
        System.out.println("Zona Horaria: " + zonaHoraria);
    }
}
```

**Main.java** (para verificación)
```java
public class Main {
    public static void main(String[] args) {
        Configuracion config1 = Configuracion.getInstancia();
        config1.setIdioma("en");
        config1.mostrarConfiguracion();

        Configuracion config2 = Configuracion.getInstancia();
        config2.mostrarConfiguracion(); // Debe mostrar los mismos valores
    }
}
```

### Cómo Ejecutar
Compila los archivos con `javac Configuracion.java Main.java` y ejecútalo usando `java Main`. Verás cómo ambas referencias apuntan a la misma instancia, mostrando los cambios compartidos. ¡Perfecto para entender el Singleton en acción!