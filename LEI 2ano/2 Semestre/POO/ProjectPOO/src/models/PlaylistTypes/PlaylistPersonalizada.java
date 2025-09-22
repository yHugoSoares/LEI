package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import java.util.Collections;
import java.util.Random;
import models.MusicTypes.*;
import models.User;


public class PlaylistPersonalizada extends Playlist {
    private int indexAtual = 0;
    private boolean aleatorio = false;

    public PlaylistPersonalizada(String nome, boolean publica) {
        super(nome, publica);
    }

    public void ativarAleatorio() {
        this.aleatorio = true;
        Collections.shuffle(getMusics());
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist personalizada: " + getNome());
        getMusics().get(indexAtual).reproduzir(); // Corrected method call
    }

    @Override
    public PlaylistPersonalizada clone() {
        PlaylistPersonalizada clone = new PlaylistPersonalizada(this.getNome(), this.isPublica());
        for (Music music : this.getMusics()) {
            clone.adicionarMusica(music);
        }
        return clone;
    }

}

