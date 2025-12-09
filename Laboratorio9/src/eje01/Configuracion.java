public class Configuracion {
  private static Configuracion instancia;
  private String idioma;
  private String zonaHoraria;

  private Configuracion() {
    this.idioma = "es";
    this.zonaHoraria = "America/Lima";
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