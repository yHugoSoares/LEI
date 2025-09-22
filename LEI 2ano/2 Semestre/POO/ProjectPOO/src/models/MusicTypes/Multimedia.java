package models.MusicTypes;

import java.util.Objects;

public class Multimedia extends Music {
    private String multimedia; // Type of multimedia (e.g., "Video", "Live Performance")

    // Constructor
    public Multimedia(String nome, String interprete, String editora, String letra, String[] notasMusicais,
                      String genero, int duracao, String multimedia) {
        super(nome, interprete, editora, letra, notasMusicais, genero, duracao);
        this.multimedia = multimedia;
    }

    // Getter
    public String getMultimedia() { return multimedia; }

    // Setter
    public void setMultimedia(String multimedia) { this.multimedia = multimedia; }

    @Override
    public String toString() {
        return super.toString() + "\nMultimedia: " + multimedia;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Multimedia that = (Multimedia) o;
        return Objects.equals(multimedia, that.multimedia);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), multimedia);
    }
}
