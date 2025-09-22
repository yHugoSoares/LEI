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
import java.util.stream.Collectors;

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
import ui.StatisticsMenu;

public class MainMenu {
    private DataManager dataManager;
    private Scanner scanner;
    private User currentUser;

    public MainMenu(DataManager dataManager, User currentUser) {
        this.dataManager = dataManager;
        this.currentUser = currentUser;
        this.scanner = new Scanner(System.in);
        // dataManager.loadMusicFromCSV("data/musicList.csv");
        dataManager.inicializarMusicas();
        dataManager.inicializarAlbuns();
    }

    public void displayMenu() {
        while (true) {
            System.out.println("\n=== SpotifUM ===");
            System.out.println("1. Ver Informações do Utilizador");
            System.out.println("2. Tocar Música");
            System.out.println("3. Tocar Playlist");
            System.out.println("4. Gerar Playlist");
            System.out.println("5. Ver Playlists Públicas");
            System.out.println("6. Remover Playlist");
            System.out.println("7. Ver Estatísticas");
            System.out.println("R. Remover Utilizador");
            System.out.println("8. Alterar Plano de Subscrição");
            System.out.println("9. Tocar Álbum");
            System.out.println("10. Ver Álbuns");
            System.out.println("11. Remover Álbum");
            System.out.println("X. Menu Inicial");
            System.out.print("Escolha: ");

            String choice = scanner.nextLine().toUpperCase();

            switch (choice) {
                case "1" -> mostrarInfoUtilizadorAtual();
                case "2" -> {
                    playMusic();
                    saveState();
                }
                case "3" -> {
                    System.out.println("");
                    playPlaylist();
                }
                case "4" -> {
                    System.out.println("");
                    generatePlaylist();
                }
                case "5" -> {
                    showPlaylists();
                }
                case "6" -> {
                    removerPlaylist();
                    saveState();
                }
                case "7" -> {
                    StatisticsMenu statisticsMenu = new StatisticsMenu(dataManager, currentUser);
                    statisticsMenu.viewStatistics();
                }
                case "8" -> alterarPlano();
                case "R" -> {
                    Utils.removeUser(dataManager, scanner);
                    saveState();
                    System.out.println("A sair...");
                    return;
                }
                case "9" -> playAlbum();
                case "10" -> {
                    showAlbuns();
                }
                case "11" -> {
                    removerAlbum();
                    saveState();
                }
                
                case "X" -> {
                    System.out.println("A sair...");
                    return;
                }
                default -> System.out.println("Invalid choice!");
            }
        }
    }
    
    //case 1
    private void mostrarInfoUtilizadorAtual() {
        System.out.println("\n=== Informações do Utilizador ===");
        System.out.println("Nome: " + currentUser.getNome());
        System.out.println("Email: " + currentUser.getEmail());
        System.out.println("Plano: " + currentUser.getPlanoSubscricao().getPlanName());
        System.out.println("Pontos: " + String.format("%.2f", currentUser.getPontos()));
    
        List<Playlist> playlists = currentUser.getPlaylists();
        System.out.println("Total de playlists: " + playlists.size());
        
        if (playlists.isEmpty()) {
            System.out.println("→ Nenhuma playlist criada ainda.");
        } else {
            System.out.println("Biblioteca Pessoal de Playlists:");
            for (Playlist p : playlists) {
                String visibilidade = p.isPublica() ? "Pública" : "Privada";
                System.out.println("- " + p.getNome() + " (" + visibilidade + ")");
            }
        }
    
        List<Album> albums = currentUser.getAlbuns();
        System.out.println("Total de álbuns: " + albums.size());
    
        if (albums.isEmpty()) {
            System.out.println("→ Nenhum álbum adicionado ainda.");
        } else {
            System.out.println("Biblioteca Pessoal de Álbuns:");
            for (Album a : albums) {
                System.out.println("- " + a.getNome());
            }
        }    }

//case2    
private void playMusic() {
    if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
        List<Music> musicas = dataManager.getMusics();
        if (musicas.isEmpty()) {
            System.out.println("Nenhuma música disponível.");
            return;
        }
        Music aleatoria = musicas.get(new Random().nextInt(musicas.size()));
        aleatoria.reproduzir();
        currentUser.reproduzirMusica();
        currentUser.adicionarMusicaOuvida(aleatoria);
        System.out.println("Reproduzindo: " + aleatoria.getNome());
        System.out.println("Letra...\n" + aleatoria.getLetra());
        return;
    }

    System.out.println("Digite o nome da música que deseja reproduzir: ");
    String nomeMusica = scanner.nextLine();
    List<Music> musicas = dataManager.getMusics();

    for (Music musica : musicas) {
        if (musica.getNome().equalsIgnoreCase(nomeMusica)) {
            musica.reproduzir();
            currentUser.reproduzirMusica();
            currentUser.adicionarMusicaOuvida(musica);
            System.out.println("Reproduzindo: " + musica.getNome() +
                    " | Total de reproduções: " + musica.getReproducoes());
            System.out.println("Letra...\n" + musica.getLetra());
            return;
        }
    }

    System.out.println("Música não encontrada.");
}
    private void saveState() {
        try {
            dataManager.saveState("data/app_state.ser");
            System.out.println(" Estado salvo com sucesso.");
        } catch (IOException e) {
            System.err.println(" Erro ao salvar estado: " + e.getMessage());
        }
    }

        // case 3
    private void playPlaylist() {

List<Playlist> availablePlaylists = getAvailablePlaylists();
    
    if (availablePlaylists.isEmpty()) {
        System.out.println("Não há playlists disponíveis.");
        return;
    }

    // Filtrar playlists para utilizadores Free
    if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
        availablePlaylists = availablePlaylists.stream()
            .filter(p -> p.isPublica() && p instanceof PlaylistAleatoria)
            .collect(Collectors.toList());
        
        if (availablePlaylists.isEmpty()) {
            System.out.println("Não há playlists disponível.");
            return;
        }
    }

    // Mostrar menu de seleção
    displayPlaylistsMenu(availablePlaylists);

    // Processar seleção
    try {
        int choice = Integer.parseInt(scanner.nextLine());
        if (choice < 1 || choice > availablePlaylists.size()) {
            System.out.println("Opção inválida!");
            return;
        }
        
        Playlist selected = availablePlaylists.get(choice - 1);
        
        // Verificação adicional para garantir que utilizadores Free só tocam playlists aleatórias e públicas
        if (currentUser.getPlanoSubscricao().getPlanName().equals("Free") && 
            (!selected.isPublica() || !(selected instanceof PlaylistAleatoria))) {
            System.out.println("O seu plano Free só permite tocar playlists aleatórias e públicas.");
            return;
        }
        
        new MusicPlayer(currentUser).playPlaylist(selected);
        
    } catch (NumberFormatException e) {
        System.out.println("Por favor, digite um número válido.");
    }
        
        // Mostrar menu de seleção
        displayPlaylistsMenu(availablePlaylists);

        // Processar seleção
        try {
            int choice = Integer.parseInt(scanner.nextLine());
            if (choice < 1 || choice > availablePlaylists.size()) {
                System.out.println("Opção inválida!");
                return;
            }
            
            Playlist selected = availablePlaylists.get(choice - 1);
            new MusicPlayer(currentUser).playPlaylist(selected);
            
        } catch (NumberFormatException e) {
            System.out.println("Por favor, digite um número válido.");
        }
    }
    
        // Métodos auxiliares
    private List<Playlist> getAvailablePlaylists() {
        List<Playlist> available = new ArrayList<>(currentUser.getPlaylists());
        dataManager.getPlaylistsPublicas().stream()
            .filter(p -> !currentUser.getPlaylists().contains(p))
            .forEach(available::add);
        return available;
    }

    private void displayPlaylistsMenu(List<Playlist> playlists) {
        System.out.println("\n=== Playlists Disponíveis ===");
        
        // Playlists do usuário
        System.out.println("--- Biblioteca Pessoal ---");
        currentUser.getPlaylists().forEach(p -> 
            System.out.printf("%d. %s (%s)%n", 
                playlists.indexOf(p) + 1, 
                p.getNome(), 
                p.isPublica() ? "Pública" : "Privada"));
        
        // Playlists públicas de outros
        System.out.println("\n--- Playlists Públicas ---");
        dataManager.getPlaylistsPublicas().stream()
            .filter(p -> !currentUser.getPlaylists().contains(p))
            .forEach(p -> System.out.printf("%d. %s (Pública)%n", 
                playlists.indexOf(p) + 1, 
                p.getNome()));
    }
    

    //caso 4
    private void generatePlaylist() {
        if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
            System.out.println("O seu plano não permite criar playlists.");
            return;
        }
    
        System.out.println("Como deseja criar a sua playlist:");
        System.out.println("1 - Aleatória");
        System.out.println("2 - Por Seleção");
        System.out.println("3 - Favoritos");
        System.out.println("4 - Favoritos Explicita");
        System.out.println("5 - Favorita Por Tempo");
        System.out.println("6 - Por Tempo e Gênero");
    
        String input = scanner.nextLine();
        int op;
        try {
            op = Integer.parseInt(input);
        } catch (NumberFormatException e) {
            System.out.println("Entrada inválida. Introduza um número entre 1 e 4.");
            return;
        }
    
        switch (op) {
            case 1 -> gerarPlaylistAleatoria();
            case 2 -> gerarPlaylistPorSelecao();
            case 3 -> {
                if (currentUser.getPlanoSubscricao().getPlanName().equals("Premium Base")) {
                    System.out.println("O seu plano não permite criar este tipo de playlists.");
                    return;
                }
                gerarPlaylistFavoritos();
            }
            case 4 -> {
                if (currentUser.getPlanoSubscricao().getPlanName().equals("Premium Base")) {
                    System.out.println("O seu plano não permite criar este tipo de playlists.");
                    return;
                }
                gerarPlaylistExplicita();
            }
            case 5 -> {
                if (currentUser.getPlanoSubscricao().getPlanName().equals("Premium Base")) {
                    System.out.println("O seu plano não permite criar este tipo de playlists.");
                    return;
                }
                gerarPlaylistFavTempo();
            }

            case 6 -> gerarPlaylistGenero();
            default -> System.out.println("Opção inválida.");
        }
    }

    private void gerarPlaylistAleatoria() {
        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine(); 
    
        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");
    
        System.out.println("Quantas músicas deseja na playlist");
        String inputQtd = scanner.nextLine();
        int qtd;
        try {
            qtd = Integer.parseInt(inputQtd);
        } catch (NumberFormatException e) {
            System.out.println("Quantidade inválida. Insira um número.");
            return;
        }
            
        List<Music> musicas = dataManager.getMusics();
        PlaylistGenerator playlistGenerator = new PlaylistGenerator();
        Playlist novaPlaylist = playlistGenerator.gerarPlaylistAleatoria(musicas, qtd, nomeP, publica); 
    
        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }

        System.out.println("Playlist adicionada ao utilizador " + currentUser.getNome());
    }
    
    private void gerarPlaylistPorSelecao(){
        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine();

        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");

        System.out.println("Quantas músicas deseja na playlist");
        String inputQtd = scanner.nextLine();
        int qtd;
        try {
            qtd = Integer.parseInt(inputQtd);
        } catch (NumberFormatException e) {
            System.out.println("Quantidade inválida. Insira um número.");
            return;
        }

                List<String> escolhidas= new ArrayList<String>();
        System.out.println("Introduza o nome das musicas a escolher");
        for(int i =0;i<qtd+1;i++){
            String nome = scanner.nextLine();
            escolhidas.add(nome);
        }

        List<Music> musicas = dataManager.getMusics();
        PlaylistGenerator playlist = new PlaylistGenerator();
        Playlist novaPlaylist = playlist.gerarPlaylistPremium(escolhidas, musicas, nomeP, publica);  
    
        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }

        System.out.println("Playlist adicionada ao utilizador " + currentUser.getNome());
    }


    private void gerarPlaylistFavoritos() {
        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine();

        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");


        System.out.println("Quantas músicas deseja na playlist");
        String inputQtd = scanner.nextLine();
        int qtd;
        try {
            qtd = Integer.parseInt(inputQtd);
        } catch (NumberFormatException e) {
            System.out.println("Quantidade inválida. Insira um número.");
            return;
        }

        List<Music> musicas = dataManager.getMusics();
        PlaylistGenerator playlistGenerator = new PlaylistGenerator();
        Playlist novaPlaylist = playlistGenerator.gerarPlaylistExplicita(currentUser, publica, qtd, nomeP); 

        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }
        System.out.println("Playlist de favoritos criada e adicionada a " + currentUser.getNome());
    }

    private void gerarPlaylistExplicita() {
        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine();

        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");


        System.out.println("Quantas músicas deseja na playlist");
        String inputQtd = scanner.nextLine();
        int qtd;
        try {
            qtd = Integer.parseInt(inputQtd);
        } catch (NumberFormatException e) {
            System.out.println("Quantidade inválida. Insira um número.");
            return;
        }

        Playlist novaPlaylist = new PlaylistExplicita(currentUser, publica, qtd, nomeP);

        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }
        System.out.println("Playlist de favoritos criada e adicionada a " + currentUser.getNome());
    }

    public void gerarPlaylistFavTempo() {

        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine();
    
        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");
    
        System.out.print("Digite o tempo máximo da playlist (em minutos): ");
        String tempoStr = scanner.nextLine();
        int tempo;
        try {
            tempo = Integer.parseInt(tempoStr) * 60;
        } catch (NumberFormatException e) {
            System.out.println("Tempo inválido. Insira um número.");
            return;
        }
    
        PlaylistGenerator playlistGenerator = new PlaylistGenerator();
        Playlist novaPlaylist = playlistGenerator.PlaylistFavTempo(currentUser, publica, tempo, nomeP);
    
        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }
        System.out.println("Playlist de favoritos criada e adicionada a " + currentUser.getNome());
    }
    
    public void gerarPlaylistGenero() {
        System.out.println("Qual o nome da playlist");
        String nomeP = scanner.nextLine();

        System.out.print("Deseja tornar a playlist pública? (s/n): ");
        String resposta = scanner.nextLine().trim().toLowerCase();
        boolean publica = resposta.equals("s");

        System.out.print("Digite o gênero da música: ");
        String genero = scanner.nextLine();
    
        System.out.print("Digite o tempo máximo da playlist (em minutos): ");
        String tempoStr = scanner.nextLine();
        int tempo;
        try {
            tempo = Integer.parseInt(tempoStr) * 60;
        } catch (NumberFormatException e) {
            System.out.println("Tempo inválido. Insira um número.");
            return;
        }
    
        Playlist novaPlaylist = new PlaylistGenero(dataManager.getMusics(), genero, tempo, nomeP);

        if (publica) {
            currentUser.addPlaylist(novaPlaylist);
            dataManager.adicionarPlaylistPublica(novaPlaylist);
        } else {
            currentUser.addPlaylist(novaPlaylist);
        }

        System.out.println("Playlist criada e adicionada a " + currentUser.getNome());

    }
    
    // case 5
    public void showPlaylists(){
        List<Playlist> playlists = dataManager.getPlaylistsPublicas();
    
        if (playlists.isEmpty()) {
            System.out.println("\nNão há playlists públicas disponíveis.");
            return;
        }
    
        System.out.println("\n--- Playlists Públicas ---");
        dataManager.getPlaylistsPublicas().stream()
            .filter(p -> !currentUser.getPlaylists().contains(p))
            .forEach(p -> System.out.printf("%d. %s (Pública)%n", 
                playlists.indexOf(p) + 1, 
                p.getNome()));

                if (!currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
                System.out.print("\nDigite o número da playlist para adicionar à sua biblioteca (0 para voltar): ");
                try {
                    int choice = Integer.parseInt(scanner.nextLine());
                    if (choice > 0 && choice <= playlists.size()) {
                        Playlist selected = playlists.get(choice - 1);
                        
                        // Verificar se já não tem esta playlist
                        if (currentUser.getPlaylists().contains(selected)) {
                            System.out.println("Você já tem esta playlist na sua biblioteca!");
                        } else {
                            // Criar uma cópia privada para o usuário
                            Playlist copia = new PlaylistBase(selected.getNome() + " (cópia)", false);
                            copia.getMusics().addAll(selected.getMusics());
                            currentUser.addPlaylist(copia);
                            System.out.println("Playlist adicionada à sua biblioteca!");
                            saveState();
                        }
                    } else if (choice != 0) {
                        System.out.println("Opção inválida!");
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Por favor, digite um número válido.");
                }
                } else{
                    System.out.println("\nO seu plano gratuito não permite adicionar playlists.");
                } 
}
        
    // case 6
    public void removerPlaylist() {

        if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
            System.out.println("O seu plano não permite remover playlists.");
            return;
        }

        List<Playlist> playlists = currentUser.getPlaylists();
    
        if (playlists.isEmpty()) {
            System.out.println("Você não tem playlists para remover.");
            return;
        }
    
        System.out.println("\n=== Suas Playlists ===");
        for (int i = 0; i < playlists.size(); i++) {
            Playlist p = playlists.get(i);
            String vis = p.isPublica() ? "Pública" : "Privada";
            System.out.println((i + 1) + ". " + p.getNome() + " (" + vis + ")");
        }
    
        System.out.print("Digite o número da playlist que deseja remover: ");
        int opcao;
        try {
            opcao = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Entrada inválida.");
            return;
        }
    
        if (opcao < 1 || opcao > playlists.size()) {
            System.out.println("Opção fora de intervalo.");
            return;
        }
    
        Playlist removida = playlists.remove(opcao - 1);
        System.out.println("Playlist '" + removida.getNome() + "' removida com sucesso!");
    }
    
    //case 7
    private void alterarPlano() {
        System.out.println("\n=== Alterar Plano de Subscrição ===");
        System.out.println("1. Free");
        System.out.println("2. Premium Base");
        System.out.println("3. Premium Top");
    
        System.out.print("Escolha o novo plano: ");
        String opcao = scanner.nextLine();
    
        SubscriptionPlan novoPlano;
        switch (opcao) {
            case "1" -> novoPlano = new FreePlan();
            case "2" -> novoPlano = new PremiumBase();
            case "3" -> novoPlano = new PremiumTop();
            default -> {
                System.out.println("Opção inválida.");
                return;
            }
        }
    
        currentUser.setPlanoSubscricao(novoPlano);
        System.out.println("Plano alterado para: " + novoPlano.getPlanName());
    }


    //case 8 
    private void playAlbum() {
        if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
            System.out.println("O seu plano não permite reproduzir álbuns completos.");
            return;
        }

        List<Album> availableAlbums = dataManager.getAlbuns();
        
        if (availableAlbums.isEmpty()) {
            System.out.println("Não há álbuns disponíveis.");
            return;
        }

        // Mostrar menu (agrupado por artista)
        System.out.println("\n=== Álbuns Disponíveis ===");
        Map<String, List<Album>> albumsPorArtista = new HashMap<>();
        for (Album album : availableAlbums) {
            albumsPorArtista.computeIfAbsent(album.getArtista(), k -> new ArrayList<>()).add(album);
        }
        
        List<Album> allAlbums = new ArrayList<>();
        int index = 1;
        for (Map.Entry<String, List<Album>> entry : albumsPorArtista.entrySet()) {
            System.out.println("\n--- " + entry.getKey() + " ---");
            for (Album album : entry.getValue()) {
                if (!allAlbums.contains(album)) { // Ensure no duplicates
                    System.out.printf("%d. %s (%d músicas)%n", index, album.getNome(), album.getMusicas().size());
                    allAlbums.add(album);
                    index++;
                }
            }
        }

        try {
            System.out.print("\nEscolha um álbum (número): ");
            int choice = Integer.parseInt(scanner.nextLine());
            
            if (choice < 1 || choice > allAlbums.size()) {
                System.out.println("Opção inválida!");
                return;
            }
            
            Album selected = allAlbums.get(choice - 1);
            
            // Use the MusicPlayer to start album playback
            MusicPlayer player = new MusicPlayer(currentUser);
            player.startAlbumPlayback(selected);
            
        } catch (NumberFormatException e) {
            System.out.println("Por favor, digite um número válido.");
        }
    }

    public void showAlbuns() {
        List<Album> albuns = dataManager.getAlbuns();

        if (albuns.isEmpty()) {
            System.out.println("\nNão há álbuns disponíveis.");
            return;
        }

        System.out.println("\n=== Álbuns Disponíveis ===");

        // Agrupar álbuns por artista
        Map<String, List<Album>> albunsPorArtista = new HashMap<>();
        for (Album album : albuns) {
            albunsPorArtista.computeIfAbsent(album.getArtista(), k -> new ArrayList<>()).add(album);
        }

        // Mostrar organizado por artista
        int index = 1;
        List<Album> allAlbums = new ArrayList<>();
        for (Map.Entry<String, List<Album>> entry : albunsPorArtista.entrySet()) {
            System.out.println("\nArtista: " + entry.getKey());
            for (Album album : entry.getValue()) {
                if (!allAlbums.contains(album)) { // Ensure no duplicates
                    System.out.println(index + ". " + album.getNome());
                    allAlbums.add(album);
                    index++;
                }
            }
        }

        if (!currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
            System.out.print("\nDigite o número do álbum para adicionar à sua biblioteca (0 para voltar): ");
            try {
                int choice = Integer.parseInt(scanner.nextLine());
                if (choice > 0 && choice <= allAlbums.size()) {
                    Album selected = allAlbums.get(choice - 1);

                    // Adicionar álbum à biblioteca pessoal
                    currentUser.addAlbum(selected);
                    System.out.println("Álbum adicionado à sua biblioteca!");
                    saveState();
                } else if (choice != 0) {
                    System.out.println("Opção inválida!");
                }
            } catch (NumberFormatException e) {
                System.out.println("Por favor, digite um número válido.");
            }
        } else {
            System.out.println("\nO seu plano não permite adicionar álbuns.");
        }
    }

    public void removerAlbum() {

        if (currentUser.getPlanoSubscricao().getPlanName().equals("Free")) {
            System.out.println("O seu plano não permite remover albuns.");
            return;
        }

        List<Album> albums = currentUser.getAlbuns();
    
        if (albums.isEmpty()) {
            System.out.println("Você não tem álbuns para remover.");
            return;
        }
    
        System.out.println("\n=== Biblioteca de Álbuns ===");
        for (int i = 0; i < albums.size(); i++) {
            Album a = albums.get(i);
            System.out.println((i + 1) + ". " + a.getNome());
        }
    
        System.out.print("Digite o número do álbum que deseja remover: ");
        int opcao;
        try {
            opcao = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Entrada inválida.");
            return;
        }
    
        if (opcao < 1 || opcao > albums.size()) {
            System.out.println("Opção fora de intervalo.");
            return;
        }
    
        Album removido = albums.remove(opcao - 1);
        System.out.println("Álbum '" + removido.getNome() + "' removido com sucesso!");
    }

}
