

public class Sensor {
    private double valor;
    
    
    public Sensor(double valor) {
        this.valor = valor;
    }

    // Getters and setters

    public boolean setPressao(double valor) {
        if (valor < 0) {
            return false;
        }
        this.valor = valor;
        return true;
    }

    public double getPressao() {
        return this.valor;
    }

    public boolean equals (Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || this.getClass() != o.getClass()) {
            return false;
        }
        Sensor s = (Sensor) o;
        return this.valor == s.getPressao();
    }
}
