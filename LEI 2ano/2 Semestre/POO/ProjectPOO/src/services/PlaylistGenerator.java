package services;

import java.util.*;
import models.User;
import models.MusicTypes.Music;
import models.PlaylistTypes.*;

public class PlaylistGenerator {

    // Gera uma playlist aleatória sem músicas repetidas
    public PlaylistAleatoria gerarPlaylistAleatoria(List<Music> todasMusicas, int quantidade, String nome, boolean publica) {
        // Ensure the input list has no duplicates
        List<Music> uniqueMusicas = todasMusicas.stream()
                                                .distinct()
                                                .toList();

        PlaylistAleatoria playlist = new PlaylistAleatoria(nome, publica);
        Set<Music> usados = new HashSet<>();
        Random random = new Random();

        if (uniqueMusicas.isEmpty()) {
            System.out.println("Não há músicas disponíveis.");
            return playlist;
        }

        int max = Math.min(quantidade, uniqueMusicas.size());

        while (usados.size() < max) {
            int index = random.nextInt(uniqueMusicas.size());
            Music musica = uniqueMusicas.get(index);
            if (!usados.contains(musica)) {
                usados.add(musica);
                playlist.adicionarMusica(musica);
            }
        }

        return playlist;
    }

    // Gera uma playlist com base numa seleção manual de nomes de músicas
    public PlaylistPersonalizada gerarPlaylistPremium(List<String> musicasEscolhidas, List<Music> todasMusicas, String nome, boolean publica) {
        PlaylistPersonalizada playlist = new PlaylistPersonalizada(nome, publica);
        for (String nomeMusica : musicasEscolhidas) {
            todasMusicas.stream()
                .filter(m -> m.getNome().equalsIgnoreCase(nomeMusica))
                .findFirst()
                .ifPresent(playlist::adicionarMusica);
        }
        return playlist;
    }

    public PlaylistExplicita gerarPlaylistExplicita(User user, boolean publica, int limite, String nome) {
        return new PlaylistExplicita(user, publica, limite, nome);
    }

    // Gera uma playlist de favoritos com base nas músicas mais ouvidas do utilizador
    public PlaylistFavoritos gerarPlaylistFavoritos(User user, boolean publica, int limite, String nome) {
        return new PlaylistFavoritos(user, publica, limite, nome);
    }

// Gera uma playlist de favoritos com um determinado tempo com base nas músicas mais ouvidas do utilizador
public PlaylistFavTempo PlaylistFavTempo(User user, boolean publica, int tempoMaximo, String nome) {
    List<Music> musicasFavoritas = user.getHistoricoOrdenado();
    List<Music> musicasSelecionadas = new ArrayList<>();
    int tempoTotal = 0;

    for (Music musica : musicasFavoritas) {
        if (tempoTotal + musica.getDuracao() <= tempoMaximo) {
            musicasSelecionadas.add(musica);
            tempoTotal += musica.getDuracao();
        } else {
            break; // Stop adding songs if the time limit is reached
        }
    }

    // Create a new playlist with the selected songs
    PlaylistFavTempo playlist = new PlaylistFavTempo(user, nome, tempoMaximo);
    for (Music musica : musicasSelecionadas) {
        playlist.adicionarMusica(musica);
    }

    return playlist;
}    
    // Gera uma playlist com base num género e um tempo máximo total
    public PlaylistGenero gerarPlaylistGenero(List<Music> musicas, String genero, int tempoMaximo, String nome) {
        return new PlaylistGenero(musicas, genero, tempoMaximo, nome);
    }
}
