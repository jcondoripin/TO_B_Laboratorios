# README.md - Ejercicio 04: Singleton en un Juego

¡Adéntrate en este ejercicio avanzado con un toque lúdico! `ControlJuego` maneja el estado global de un juego (nivel, puntaje, vidas) vía Singleton, permitiendo que módulos como jugador o enemigos modifiquen y consulten los mismos datos en tiempo real, manteniendo todo sincronizado.

### Código Fuente
**ControlJuego.java**
```java
public class ControlJuego {
    private static ControlJuego instancia;
    private int nivel = 1;
    private int puntaje = 0;
    private int vidas = 3;

    private ControlJuego() {}

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
```

**Main.java** (simulación de módulos)
```java
public class Main {
    public static void main(String[] args) {
        // Módulo Jugador
        ControlJuego juego = ControlJuego.getInstancia();
        juego.agregarPuntaje(100);
        System.out.println("Puntaje desde Jugador: " + juego.getPuntaje());

        // Módulo Enemigo
        ControlJuego mismoJuego = ControlJuego.getInstancia();
        mismoJuego.perderVida();
        System.out.println("Vidas desde Enemigo: " + mismoJuego.getVidas());

        // Módulo Interfaz
        System.out.println("Nivel desde Interfaz: " + mismoJuego.getNivel());
    }
}
```

### Cómo Ejecutar
Compila con `javac ControlJuego.java Main.java` y corre `java Main`. Ve los cambios reflejados en consola desde diferentes "módulos". ¡Perfecto para estados globales en juegos dinámicos!
