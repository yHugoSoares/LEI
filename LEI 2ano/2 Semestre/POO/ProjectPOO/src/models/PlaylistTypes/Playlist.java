
package models.PlaylistTypes;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import models.MusicTypes.*;

public abstract class Playlist implements Serializable {
    private String nome;
    private List<Music> musics;
    private boolean publica;

    // Construtor
    public Playlist(){
        this.musics = new ArrayList<>();
        this.nome =" ";
        this.publica = false;
    }

    public Playlist(String nome, boolean publica) {
        this.nome = nome;
        this.musics = new ArrayList<>();
        this.publica = publica;
    }

    public Playlist(Playlist p){
        this.nome = p.getNome();
        this.musics = p.getMusics();
        this.publica = p.isPublica();
    }

    // Getters 
    public String getNome() { return nome; }
    public List<Music> getMusics() { return new ArrayList<>(musics); }

    // Setters
    public void setNome(String nome) { this.nome = nome; }
    public void setPublica(boolean publica) { this.publica = publica; }

    // Métodos
    public boolean isPublica() {
        return publica;
    }

    public void adicionarMusica(Music music) {
        this.musics.add(music);
    }

    public void removerMusica(Music music) {
        this.musics.remove(music);
    }

    public void reproduzPlaylist() {
        System.out.println("Playing playlist: " + nome);
        for (Music music : musics) {
            System.out.println("Now playing: " + music.getNome());
            music.reproduzir();
        }
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Playlist: ").append(nome).append("\n");
        sb.append("Músicas: ").append(musics.size()).append("\n");
        sb.append("Pública: ").append(publica).append("\n");
        return sb.toString();
    }

    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Playlist playlist = (Playlist) o;
        return nome.equals(playlist.getNome()) &&
               publica == playlist.isPublica() &&
               musics.equals(playlist.getMusics());
     }

    @Override
    public abstract Playlist clone();
    
}
