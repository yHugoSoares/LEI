package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import models.MusicTypes.*;
import models.User;

public class PlaylistBase extends Playlist {
    public PlaylistBase(String nome, boolean publica) {
        super(nome, publica);
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist Base: " + getNome());
        for (Music music : getMusics()) {
            music.reproduzir(); 
        }
    }

    @Override
    public PlaylistBase clone() {
        PlaylistBase clone = new PlaylistBase(this.getNome(), this.isPublica());
        for (Music music : this.getMusics()) {
            clone.adicionarMusica(music);
        }
        return clone;
    }   




}