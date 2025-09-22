package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import models.MusicTypes.*;
import models.User;


public class PlaylistAleatoria extends Playlist {
    public PlaylistAleatoria(String nome, boolean publica) {
        super(nome, publica);
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist aleatória: " + getNome());
        for (Music music : getMusics()) {
            music.reproduzir(); // Corrected method call
        }
    }

    @Override
    public PlaylistAleatoria clone() {
        PlaylistAleatoria clone = new PlaylistAleatoria(this.getNome(), this.isPublica());
        for (Music music : this.getMusics()) {
            clone.adicionarMusica(music);
        }
        return clone;
    }   
}

