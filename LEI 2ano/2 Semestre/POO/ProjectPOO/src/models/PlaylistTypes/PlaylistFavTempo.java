package models.PlaylistTypes;

import java.util.ArrayList;
import java.util.List;
import models.MusicTypes.Music;
import models.User;

public class PlaylistFavTempo extends Playlist {
    public PlaylistFavTempo(User user, String nome, int tempoMax) {
        super(nome, true);
        List<Music> musicas = user.getHistoricoOrdenado();
        int tempoTotal = 0;

        for (Music m : musicas) {
            if (tempoTotal + m.getDuracao() <= tempoMax) {
                adicionarMusica(m);
                tempoTotal += m.getDuracao();
            }
        }
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist de favoritos: " + getNome());
        super.reproduzPlaylist();
    }

    @Override
    public PlaylistFavTempo clone() {
        PlaylistFavTempo clone = new PlaylistFavTempo(null, this.getNome(), 0); // Adjust as needed
        clone.getMusics().addAll(this.getMusics());
        return clone;
    }
}
