# README.md - Ejercicio 03: Conexión Simulada a Base de Datos

¡Sumérgete en este ejercicio aplicado al mundo real! `ConexionBD` simula una conexión única a una BD usando Singleton, controlando el estado (conectado/desconectado) para evitar recursos innecesarios. Métodos como `conectar` y `estado` hacen que sea fácil gestionar y verificar la conexión en un entorno controlado.

### Código Fuente
**ConexionBD.java**
```java
public class ConexionBD {
    private static ConexionBD instancia;
    private boolean conectada = false;

    private ConexionBD() {}

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
```

**Main.java** (para prueba)
```java
public class Main {
    public static void main(String[] args) {
        ConexionBD bd1 = ConexionBD.getInstancia();
        bd1.conectar();
        bd1.estado();

        ConexionBD bd2 = ConexionBD.getInstancia();
        bd2.estado(); // Mismo estado
        bd2.desconectar();
    }
}
```

### Cómo Ejecutar
Compila con `javac ConexionBD.java Main.java` y ejecuta `java Main`. Observa los mensajes en consola que confirman el estado compartido. ¡Genial para simular recursos críticos como conexiones a BD!
