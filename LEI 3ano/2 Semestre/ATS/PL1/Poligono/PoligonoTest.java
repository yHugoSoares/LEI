import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import org.junit.jupiter.api.Test;

public class PoligonoTest {

    @Test
    public void testPontoDistancia() {
        Ponto p1 = new Ponto(0, 0);
        Ponto p2 = new Ponto(3, 4);
        assertEquals(5.0, p1.distancia(p2), 1e-6);
    }

    @Test
    public void testTrianguloArea() {
        Triangulo t = new Triangulo(
            new Ponto(0, 0),
            new Ponto(4, 0),
            new Ponto(0, 3)
        );
        assertEquals(6.0, t.areaTriangulo(), 1e-6);
    }

    @Test
    public void testRetanguloArea() {
        Retangulo r = new Retangulo(
            new Ponto(0, 0),
            new Ponto(4, 0),
            new Ponto(4, 3),
            new Ponto(0, 3)
        );
        assertEquals(12.0, r.areaQuadrado(), 1e-6);
    }

    @Test
    public void testPoligonoConvexoArea() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(4, 0),
                new Ponto(4, 3),
                new Ponto(0, 3)
            )
        );
        assertEquals(12.0, p.area(), 1e-6);
    }

    @Test
    public void testPoligonoFechada() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(1, 0),
                new Ponto(1, 1),
                new Ponto(0, 1)
            )
        );
        assertTrue(p.fechada());
    }
}
