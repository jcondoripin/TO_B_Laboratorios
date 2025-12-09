public class ControlJuego {
  private static ControlJuego instancia;
  private int nivel = 1;
  private int puntaje = 0;
  private int vidas = 3;

  private ControlJuego() {
  }

  public static ControlJuego getInstancia() {
    if (instancia == null) {
      instancia = new ControlJuego();
    }
    return instancia;
  }

  public int getNivel() {
    return nivel;
  }

  public void setNivel(int nivel) {
    this.nivel = nivel;
  }

  public int getPuntaje() {
    return puntaje;
  }

  public void agregarPuntaje(int puntos) {
    this.puntaje += puntos;
  }

  public int getVidas() {
    return vidas;
  }

  public void perderVida() {
    if (vidas > 0) {
      vidas--;
    }
  }
}
