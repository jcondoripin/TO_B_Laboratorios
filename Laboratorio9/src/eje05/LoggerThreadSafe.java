import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class LoggerThreadSafe {
  private static volatile LoggerThreadSafe instancia;
  private static final String ARCHIVO = "bitacora.log";
  private static final Object lock = new Object();

  private LoggerThreadSafe() {
  }

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
    synchronized (lock) {
      try (BufferedWriter writer = new BufferedWriter(new FileWriter(ARCHIVO, true))) {
        writer.write(entrada);
      } catch (IOException e) {
        System.err.println("Error al escribir en el log: " + e.getMessage());
      }
    }
  }
}
