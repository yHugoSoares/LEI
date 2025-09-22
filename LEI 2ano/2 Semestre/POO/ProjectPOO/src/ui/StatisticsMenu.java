package ui;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Random;
import java.util.Scanner;
import models.*;
import models.MusicTypes.*;
import models.PlaylistTypes.*;
import models.SubscriptionPlans.FreePlan;
import models.SubscriptionPlans.PremiumBase;
import models.SubscriptionPlans.PremiumTop;
import models.SubscriptionPlans.SubscriptionPlan;
import services.*;
import services.MusicPlayer.*;
import utils.*;


public class StatisticsMenu {

    private DataManager dataManager;
    private Scanner scanner;

    public StatisticsMenu(DataManager dataManager, User currentUser) {
        this.dataManager = dataManager;
        this.scanner = new Scanner(System.in);
    }

    
public void viewStatistics(){
    System.out.println("\nStatistics");
        System.out.println("1. Musica mais reproduzida");
        System.out.println("2. Interprete mais escutado");
        System.out.println("3. Utilizador mais ativo");
        System.out.println("4. Utilizador com mais pontos");
        System.out.println("5. Tipo de musica mais reproduzida");
        System.out.println("6. Quantas playlists publicas existem");
        System.out.println("7. Utilizador que possui mais playlists");
        System.out.println("X. Menu SpotifUM");
        System.out.print("Enter choice: ");

        char choice = scanner.nextLine().charAt(0);

        switch (choice) {
            case '1' -> {
                topMusica();
                break;
            }
            case '2' -> {
                topInterprete();
                break;
            }
            case '3' -> {
                utilizadorAtivo();
                break;
            }
            case '4' -> {
                utilizadorMaisPontos();
                break;
            }
            case '5'-> {
                tipoMusicaMaisReproduzida();
                break;
            }
            case '6'-> {
                totalPlaylistsPublicas();
                break;
            }
            case '7'-> {
                utilizadorMaisPlaylists();
                break;
            }
            case 'x' -> {
                System.out.println("A sair...");
                return;
            }
            default -> System.out.println("Invalid choice!");
        }
}

public void topMusica(){
    List<Music> musicas = dataManager.getMusics();
    Music topMusic = musicas.stream()
                    .max(Comparator.comparingInt(Music::getReproducoes))
                    .orElse(null);
    System.out.println("A musica mais reproduzida é "+ topMusic);
}

public void topInterprete(){
    List<Music> musicas = dataManager.getMusics();
    Map<String,Integer> interprete= new HashMap<>();
    for (Music music : musicas) {
        interprete.put(music.getInterprete(),musicas.stream()
        .filter(m -> m.getInterprete().equals(music.getInterprete()))
        .mapToInt(Music :: getReproducoes)
        .sum());
    }
    Map.Entry<String,Integer> topmusico = interprete.entrySet().stream()
    .max(Comparator.comparingInt(Map.Entry:: getValue))
    .orElse(null);
    System.out.println("O interprete mais reproduzido é "+ topmusico.getKey());
}

public void utilizadorAtivo() {
    List<User> users = dataManager.getUsers();

    User maisAtivo = users.stream()
            .max(Comparator.comparingInt(User::getTempoTotalOuvido))
            .orElse(null);

    if (maisAtivo != null && maisAtivo.getTempoTotalOuvido() > 0) {
        int tempo = maisAtivo.getTempoTotalOuvido();
        int minutos = tempo / 60;
        int segundos = tempo % 60;

        System.out.println("Utilizador mais ativo: " + maisAtivo.getNome() +
                           " (" + minutos + "m " + segundos + "s de música ouvida)");
    } else {
        System.out.println("Nenhum utilizador ouviu músicas ainda.");
    }
}


public void utilizadorMaisPontos(){
    List<User> utilizadores = dataManager.getUsers();
    User max = utilizadores.stream()
               .max(Comparator.comparingDouble(User::getPontos))
               .orElse(null);
    System.out.println("O utilizador com mais pontos é: " + max);
}

public void tipoMusicaMaisReproduzida(){
    List<Music> musicas = dataManager.getMusics();
    Map<String, Integer> tipo = new HashMap<>();
    for(Music musi : musicas){
        tipo.put(musi.getGenero(), musicas.stream()
                .filter(m -> m.getGenero().equals(musi.getGenero()))
                .mapToInt(Music :: getReproducoes)
                .sum());
    }
    Map.Entry<String, Integer> generoTop = tipo.entrySet().stream()
                                           .max(Comparator.comparingInt(Map.Entry :: getValue))
                                           .orElse(null);
    System.out.println("O tipo de musica mais reproduzido é: " + generoTop.getKey());
}

public void totalPlaylistsPublicas(){
    List<User> users = dataManager.getUsers();
    int total = 0;

    for(User user : users){
        for (Playlist playlist : user.getPlaylists()) {
            if(playlist.isPublica()){
                total++;
            }
        }
    }
    System.out.println("O total de playlists publicas é " + total);
}

public void utilizadorMaisPlaylists(){
    List<User> users = dataManager.getUsers();

    User topUser = users.stream()
        .max(Comparator.comparingInt(u -> u.getPlaylists().size()))
        .orElse(null);

    if (topUser == null || topUser.getPlaylists().isEmpty()) {
        System.out.println("Nenhum utilizador possui playlists.");
    } else {
        System.out.println("Utilizador com mais playlists: " + topUser.getNome() +
                           " (" + topUser.getPlaylists().size() + " playlists)");
    }
}

}