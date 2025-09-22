package models.PlaylistTypes;

import java.util.*;
import java.util.stream.Collectors;
import models.SubscriptionPlans.*;
import models.MusicTypes.*;
import models.User;


public class PlaylistFavoritos extends Playlist {
    public PlaylistFavoritos(User user, boolean publica, int quantidade, String nome) {
        super(nome, publica);

        List<Music> historicoOrdenado = user.getHistoricoOrdenado();

        int limite = Math.min(quantidade, historicoOrdenado.size());

        for (int i = 0; i < limite; i++) {
            adicionarMusica(historicoOrdenado.get(i));
        }
    }

    @Override
    public void reproduzPlaylist() {
        System.out.println("Reproduzindo favoritos de " + getNome());
        super.reproduzPlaylist();
    }

    @Override
    public PlaylistFavoritos clone() {
        return new PlaylistFavoritos(new User("Clone", "clone@example.com", "N/A", new FreePlan()), this.isPublica(), 10, this.getNome());
    }
    
}
