package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import models.MusicTypes.*;

public class Album implements Serializable {
    private String nome;
    private String artista;
    private String editora;
    private String anoLancamento;
    private String genero;
    private boolean publica;
    private List<Music> musicas;


    // Construtor
    public Album() {
        this.nome = "";
        this.artista = "";
        this.editora = "";
        this.anoLancamento = "";
        this.genero = "";
        this.publica = false;
        this.musicas = new ArrayList<>();
    }

    public Album(String nome, String artista, String editora, String anoLancamento, String genero, boolean publica) {
        this.nome = nome;
        this.artista = artista;
        this.editora = editora;
        this.anoLancamento = anoLancamento;
        this.genero = genero;
        this.publica = publica;
        this.musicas = new ArrayList<>();
    }
    
    public Album(Album a) {
        this.nome = a.getNome();
        this.artista = a.getArtista();
        this.editora = a.getEditora();
        this.anoLancamento = a.getAnoLancamento();
        this.genero = a.getGenero();
        this.publica = a.isPublica();
        this.musicas = new ArrayList<>(a.getMusicas()); 
    }
    
    // Getters
    public String getNome() { return nome; }
    public String getArtista() { return artista; }
    public String getEditora() { return editora; }
    public String getAnoLancamento() { return anoLancamento; }
    public String getGenero() { return genero; }
    public boolean isPublica() { return publica; }
    public List<Music> getMusicas() { return new ArrayList<>(musicas); }

    // Setters
    public void setNome(String nome) { this.nome = nome; }
    public void setArtista(String artista) { this.artista = artista; }

    // Métodos
    public void addAlbum(Music musica) {
        this.musicas.add(musica);
    }

    public void removerMusica(Music musica) {
        this.musicas.remove(musica);
    }

    public void reproduzir() {
        System.out.println("Playing playlist: " + nome);
        for (Music music : musicas) {
            System.out.println("Now playing: " + music.getNome());
            
            music.reproduzir();
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Album: ").append(nome).append("\n");
        sb.append("Artista: ").append(artista).append("\n");
        sb.append("Editora: ").append(editora).append("\n");
        sb.append("Ano de Lançamento: ").append(anoLancamento).append("\n");
        sb.append("Gênero: ").append(genero).append("\n");
        sb.append("Público: ").append(publica ? "Sim" : "Não").append("\n");
        sb.append("Músicas:\n");
        for (Music musica : musicas) {
            sb.append(musica.getNome()).append("\n");
        }
        return sb.toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Album)) return false;
        Album album = (Album) o;
        return publica == album.publica &&
                nome.equals(album.nome) &&
                artista.equals(album.artista) &&
                editora.equals(album.editora) &&
                anoLancamento.equals(album.anoLancamento) &&
                genero.equals(album.genero);
    }

}
