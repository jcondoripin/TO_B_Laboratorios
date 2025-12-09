public class Main {
  public static void main(String[] args) {
    ConexionBD bd1 = ConexionBD.getInstancia();
    bd1.conectar();
    bd1.estado();

    ConexionBD bd2 = ConexionBD.getInstancia();
    bd2.estado();
    bd2.desconectar();
  }
}