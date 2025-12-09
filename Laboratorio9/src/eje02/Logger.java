import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Logger {
  private static Logger instancia;
  private static final String ARCHIVO = "bitacora.log";

  private Logger() {
  }

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
