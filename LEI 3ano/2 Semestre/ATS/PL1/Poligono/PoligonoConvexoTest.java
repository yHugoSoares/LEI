import static org.junit.jupiter.api.Assertions.*;

import java.util.Arrays;
import java.util.List;
import org.junit.jupiter.api.Test;

public class PoligonoConvexoTest {

    @Test
    public void testAreaTrianguloIgualAreaPoligono() {
        // Triângulo: área deve ser igual ao único triângulo formado
        Ponto a = new Ponto(0, 0);
        Ponto b = new Ponto(4, 0);
        Ponto c = new Ponto(0, 3);
        PoligonoConvexo p = new PoligonoConvexo(Arrays.asList(a, b, c));
        double areaPoligono = p.area();
        Triangulo t = new Triangulo(a, b, c);
        assertEquals(t.areaTriangulo(), areaPoligono, 1e-6);
    }

    @Test
    public void testAreaQuadrado() {
        // Quadrado 2x2
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(2, 0),
                new Ponto(2, 2),
                new Ponto(0, 2)
            )
        );
        assertEquals(4.0, p.area(), 1e-6);
    }

    @Test
    public void testCloneNotNull() {
        PoligonoConvexo p = new PoligonoConvexo();
        assertNotNull(p.clone());
    }

    @Test
    public void testTriangulaQuadrilatero() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(4, 0),
                new Ponto(4, 3),
                new Ponto(0, 3)
            )
        );
        List<Triangulo> triangulos = p.triangula();
        assertEquals(2, triangulos.size());
    }

    @Test
    public void testTriangulaPentagono() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(2, 0),
                new Ponto(3, 2),
                new Ponto(1, 4),
                new Ponto(-1, 2)
            )
        );
        List<Triangulo> triangulos = p.triangula();
        assertEquals(3, triangulos.size());
    }

    @Test
    public void testTriangulaHexagono() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(2, 0),
                new Ponto(3, 1),
                new Ponto(2, 2),
                new Ponto(0, 2),
                new Ponto(-1, 1)
            )
        );
        List<Triangulo> triangulos = p.triangula();
        assertEquals(4, triangulos.size());
    }

    @Test
    public void testAreaRetangulo() {
        PoligonoConvexo p = new PoligonoConvexo(
            Arrays.asList(
                new Ponto(0, 0),
                new Ponto(5, 0),
                new Ponto(5, 2),
                new Ponto(0, 2)
            )
        );
        Retangulo r = new Retangulo(
            new Ponto(0, 0),
            new Ponto(5, 0),
            new Ponto(5, 2),
            new Ponto(0, 2)
        );
        assertEquals(r.area(), p.area(), 1e-6);
    }
}
