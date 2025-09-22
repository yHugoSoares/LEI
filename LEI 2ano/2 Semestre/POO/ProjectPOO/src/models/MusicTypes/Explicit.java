package models.MusicTypes;

public class Explicit extends Music {
    private int explicit;

    public Explicit(String nome, String interprete, String editora, String letra, String[] notasMusicais, String genero, int duracao, int explicit) {
        super(nome, interprete, editora, letra, notasMusicais, genero, duracao);
        this.explicit = explicit;
    }

    public int getExplicit() { return explicit; }
    public void setExplicit(int explicit) { this.explicit = explicit; }

    @Override
    public String toString() {
        return super.toString() + "\nExplicit: " + explicit;
    }
}
