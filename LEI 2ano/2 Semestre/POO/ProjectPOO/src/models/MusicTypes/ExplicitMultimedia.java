package models.MusicTypes;

import java.util.Objects;

public class ExplicitMultimedia extends Music {
    private int explicit; // 0 for non-explicit, 1 for explicit
    private String multimedia; // Type of multimedia (e.g., "Video", "Live Performance")

    // Constructor
    public ExplicitMultimedia(String nome, String interprete, String editora, String letra, String[] notasMusicais,
                              String genero, int duracao, int explicit, String multimedia) {
        super(nome, interprete, editora, letra, notasMusicais, genero, duracao);
        this.explicit = explicit;
        this.multimedia = multimedia;
    }

    // Getters
    public int getExplicit() { return explicit; }
    public String getMultimedia() { return multimedia; }

    // Setters
    public void setExplicit(int explicit) { this.explicit = explicit; }
    public void setMultimedia(String multimedia) { this.multimedia = multimedia; }

    @Override
    public String toString() {
        return super.toString() + "\nExplicit: " + explicit + "\nMultimedia: " + multimedia;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        ExplicitMultimedia that = (ExplicitMultimedia) o;
        return explicit == that.explicit && Objects.equals(multimedia, that.multimedia);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), explicit, multimedia);
    }
}
