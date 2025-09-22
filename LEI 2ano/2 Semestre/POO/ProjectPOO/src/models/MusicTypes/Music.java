package models.MusicTypes;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Objects;

public abstract class Music implements Serializable {
    private String nome;
    private String autor;
    private String editora;
    private String letra;
    private String[] notasMusicais;
    private String genero;
    private int duracao; // segundos
    private int reproducoes;

    // Constructor
    public Music(String nome, String autor, String editora, String letra, String[] notasMusicais, String genero, int duracao) {
        this.nome = nome;
        this.autor = autor;
        this.editora = editora;
        this.letra = letra;
        this.notasMusicais = notasMusicais;
        this.genero = genero;
        this.duracao = duracao;
        this.reproducoes = 0;
    }

    // Getters
    public String getNome() { return nome; }
    public String getInterprete() { return autor; }
    public String getEditora() { return editora; }
    public String getLetra() { return letra; }
    public String[] getNotasMusicais() { return notasMusicais; }
    public String getGenero() { return genero; }
    public int getDuracao() { return duracao; }
    public int getReproducoes() { return reproducoes; }

    // Setters
    public void setLetra(String letra) { this.letra = letra; }
    public void setGenero(String genero) { this.genero = genero; }

    // Methods
    public void reproduzir() {
        this.reproducoes++;
    }

    @Override
    public String toString() {
        return "Nome: " + nome + "\nInterprete: " + autor + "\nEditora: " + editora +
               "\nLetra: " + letra + "\nNotas Musicais: " + Arrays.toString(notasMusicais) +
               "\nGenero: " + genero + "\nDuracao: " + duracao + "\nReproducoes: " + reproducoes;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Music music = (Music) o;
        return duracao == music.duracao &&
               reproducoes == music.reproducoes &&
               Objects.equals(nome, music.nome) &&
               Objects.equals(autor, music.autor) &&
               Objects.equals(editora, music.editora) &&
               Objects.equals(letra, music.letra) &&
               Arrays.equals(notasMusicais, music.notasMusicais) &&
               Objects.equals(genero, music.genero);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(nome, autor, editora, letra, genero, duracao, reproducoes);
        result = 31 * result + Arrays.hashCode(notasMusicais);
        return result;
    }
}
