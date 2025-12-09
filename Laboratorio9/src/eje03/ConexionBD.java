public class ConexionBD {
  private static ConexionBD instancia;
  private boolean conectada = false;

  private ConexionBD() {
  }

  public static ConexionBD getInstancia() {
    if (instancia == null) {
      instancia = new ConexionBD();
    }
    return instancia;
  }

  public void conectar() {
    if (!conectada) {
      conectada = true;
      System.out.println("Conexión establecida.");
    } else {
      System.out.println("Ya está conectada.");
    }
  }

  public void desconectar() {
    if (conectada) {
      conectada = false;
      System.out.println("Conexión cerrada.");
    } else {
      System.out.println("No hay conexión activa.");
    }
  }

  public void estado() {
    System.out.println("Estado: " + (conectada ? "Conectada" : "Desconectada"));
  }
}