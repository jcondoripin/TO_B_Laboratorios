public class Main {
  public static void main(String[] args) {
    Configuracion config1 = Configuracion.getInstancia();
    config1.setIdioma("en");
    config1.mostrarConfiguracion();

    Configuracion config2 = Configuracion.getInstancia();
    config2.mostrarConfiguracion();
  }
}