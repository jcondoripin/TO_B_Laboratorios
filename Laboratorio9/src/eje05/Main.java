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
