package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import models.MusicTypes.*;
import models.User;


public class PlaylistGenero extends Playlist {
    public PlaylistGenero(List<Music> todas, String genero, int tempoMax, String nome) {
        super(nome, true);
        int tempoTotal = 0;

        for (Music m : todas) {
            if (m.getGenero().equalsIgnoreCase(genero)) {
                if (tempoTotal + m.getDuracao() <= tempoMax) {
                    adicionarMusica(m);
                    tempoTotal += m.getDuracao();
                }
            }
        }
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist do género: " + getNome());
        super.reproduzPlaylist();
    }

    @Override
    public PlaylistGenero clone() {
        List<Music> musics = new ArrayList<>(this.getMusics());
        String genero = this.getNome().split(" ")[2]; // Extract genre from the name
        int tempoMax = musics.stream().mapToInt(Music::getDuracao).sum(); // Calculate total duration
        PlaylistGenero clone = new PlaylistGenero(musics, genero, tempoMax, this.getNome());
        return clone;
    }
}

    

