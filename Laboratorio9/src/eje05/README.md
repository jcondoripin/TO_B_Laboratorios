# README.md - Ejercicio 05: Singleton Thread-Safe

¡Enfrenta este desafío con multihilos! Modificamos el Logger para que sea seguro en entornos concurrentes, usando double-checked locking y sincronización para evitar instancias múltiples o corrupción de archivos, ideal para apps paralelas.

### Código Fuente
**LoggerThreadSafe.java**
```java
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class LoggerThreadSafe {
    private static volatile LoggerThreadSafe instancia;
    private static final String ARCHIVO = "bitacora.log";
    private static final Object lock = new Object();

    private LoggerThreadSafe() {}

    public static LoggerThreadSafe getInstancia() {
        if (instancia == null) {
            synchronized (lock) {
                if (instancia == null) {
                    instancia = new LoggerThreadSafe();
                }
            }
        }
        return instancia;
    }

    public void log(String mensaje) {
        String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
        String entrada = timestamp + " - " + mensaje + "\n";
        synchronized (lock) { // Sincronizamos la escritura para evitar corrupción en multihilo
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(ARCHIVO, true))) {
                writer.write(entrada);
            } catch (IOException e) {
                System.err.println("Error al escribir en el log: " + e.getMessage());
            }
        }
    }
}
```

**Main.java** (prueba multihilo)
```java
public class Main {
    public static void main(String[] args) {
        Thread hilo1 = new Thread(() -> {
            LoggerThreadSafe logger = LoggerThreadSafe.getInstancia();
            logger.log("Mensaje desde hilo 1");
        });

        Thread hilo2 = new Thread(() -> {
            LoggerThreadSafe logger = LoggerThreadSafe.getInstancia();
            logger.log("Mensaje desde hilo 2");
        });

        hilo1.start();
        hilo2.start();
    }
}
```

### Cómo Ejecutar
Compila con `javac LoggerThreadSafe.java Main.java` y ejecuta `java Main`. Chequea `bitacora.log` para ver registros sin conflictos. ¡Esencial para programación concurrente!