package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import services.*;
import models.MusicTypes.*;
import models.User;

public class PlaylistExplicita extends Playlist {
	private List<Music> todasMusicas;
	private User user;
	
    public PlaylistExplicita(User user, boolean publica, int quantidade, String nome) {
        super(nome, publica);

        List<Music> historicoOrdenado = user.getHistoricoOrdenado();

        int limite = Math.min(quantidade, historicoOrdenado.size());

        for (int i = 0; i < limite; i++) {
            Music music = historicoOrdenado.get(i); // Define the variable
            if (music instanceof Explicit) {
                adicionarMusica(music);
            }
        }
    }


    
    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo playlist explicita: " + getNome());
		for (Music music : this.getMusics()) {
			music.reproduzir();
		}
    }

    @Override
    public PlaylistExplicita clone() {
        PlaylistExplicita clone = new PlaylistExplicita(this.user, this.isPublica(), this.getMusics().size(), this.getNome()); // Pass the User object
        for (Music music : this.getMusics()) {
            clone.adicionarMusica(music);
        }
        return clone;
    }
	
}
