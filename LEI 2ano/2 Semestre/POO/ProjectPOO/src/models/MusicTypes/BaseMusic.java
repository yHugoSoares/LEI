package models.MusicTypes;

public class BaseMusic extends Music {

    // Constructor
    public BaseMusic(String nome, String interprete, String editora, String letra, String[] notasMusicais, String genero, int duracao) {
        super(nome, interprete, editora, letra, notasMusicais, genero, duracao);
    }

    // Additional methods specific to BaseMusic (if any) can be added here
    @Override
    public String toString() {
        return super.toString(); // Use the toString method from the Music superclass
    }
}
