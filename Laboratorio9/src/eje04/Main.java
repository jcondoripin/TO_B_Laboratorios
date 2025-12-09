public class Main {
  public static void main(String[] args) {
    ControlJuego juego = ControlJuego.getInstancia();
    juego.agregarPuntaje(100);
    System.out.println("Puntaje desde Jugador: " + juego.getPuntaje());

    ControlJuego mismoJuego = ControlJuego.getInstancia();
    mismoJuego.perderVida();
    System.out.println("Vidas desde Enemigo: " + mismoJuego.getVidas());

    System.out.println("Nivel desde Interfaz: " + mismoJuego.getNivel());
  }
}