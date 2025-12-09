# README.md - Ejercicio 02: Singleton con Recursos Compartidos

¡Explora este ejercicio intermedio donde el Singleton brilla en el manejo de recursos! La clase `Logger` registra mensajes en un archivo único `bitacora.log`, agregando timestamps automáticos para un seguimiento preciso. Esto centraliza el logging, previniendo conflictos en aplicaciones grandes, y maneja errores de escritura para mayor fiabilidad.

### Código Fuente
**Logger.java**
```java
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Logger {
    private static Logger instancia;
    private static final String ARCHIVO = "bitacora.log";

    private Logger() {}

    public static Logger getInstancia() {
        if (instancia == null) {
            instancia = new Logger();
        }
        return instancia;
    }

    public void log(String mensaje) {
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        String entrada = timestamp + " - " + mensaje + "\n";
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(ARCHIVO, true))) {
            writer.write(entrada);
        } catch (IOException e) {
            System.err.println("Error al escribir en el log: " + e.getMessage());
        }
    }
}
```

**Main.java** (para prueba)
```java
public class Main {
    public static void main(String[] args) {
        Logger logger1 = Logger.getInstancia();
        logger1.log("Inicio de aplicación");

        Logger logger2 = Logger.getInstancia();
        logger2.log("Evento importante"); // Escribe en el mismo archivo
    }
}
```

### Cómo Ejecutar
Compila con `javac Logger.java Main.java` y corre `java Main`. Revisa `bitacora.log` para ver los mensajes timestamped. ¡Ideal para ver cómo el Singleton unifica el acceso a archivos compartidos!
