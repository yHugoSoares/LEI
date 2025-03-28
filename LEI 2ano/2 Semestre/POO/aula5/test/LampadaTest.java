import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.*;


public class LampadaTest {
    @Test
    public void testLampada() {
        Lampada l = new Lampada();
        assertEquals(false, l.getLigada());
        l.liga();
        assertEquals(true, l.getLigada());
        l.desliga();
        assertEquals(false, l.getLigada());
        l.liga();
        assertEquals(true, l.getLigada());
        l.alteraEstado();
        assertEquals(false, l.getLigada());
        l.alteraEstado();
        assertEquals(true, l.getLigada());
    }
}
