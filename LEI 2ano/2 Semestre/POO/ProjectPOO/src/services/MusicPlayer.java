package services;

import models.*;
import models.MusicTypes.Music;
import models.PlaylistTypes.Playlist;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class MusicPlayer {
    private Playlist currentPlaylist;
    private int currentTrackIndex;
    private boolean isPlaying;
    private Thread playbackThread;
    private User currentUser;

    public MusicPlayer(User currentUser) {
        this.currentUser = currentUser;
    }

    private List<Music> currentTracksOrder;

    public void playPlaylist(Playlist playlist) {
        this.currentPlaylist = playlist;
        this.currentTracksOrder = new ArrayList<>(playlist.getMusics());
        Collections.shuffle(this.currentTracksOrder);
        this.currentTrackIndex = 0;
        this.isPlaying = true;
        
        System.out.println("\nIniciando reprodução da playlist: " + playlist.getNome());
        startPlayback();
    }
    
    public void startPlayback() {
        Scanner controlScanner = new Scanner(System.in);
        
        while (isPlaying && currentTrackIndex < currentTracksOrder.size()) {
            Music currentMusic = currentTracksOrder.get(currentTrackIndex);
            displayTrackInfo(currentMusic);
            
            System.out.println("\nControlos: [>] Próxima | [<] Anterior | [R] Shuffle | [S] Sair");
            
            long startTime = System.currentTimeMillis();
            boolean userResponded = false;
            
            while (!userResponded && (System.currentTimeMillis() - startTime) < 10) {
                if (controlScanner.hasNextLine()) {
                    String command = controlScanner.nextLine().toLowerCase();
                    handleUserCommand(command);
                    userResponded = true;
                } else {
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
            }
            
            if (!userResponded) {
                System.out.println("\nAvançando para próxima música...");
                nextTrack();
            }
        }
        
        if (currentTrackIndex >= currentTracksOrder.size()) {
            System.out.println("\nFim da playlist " + currentPlaylist.getNome());
        }
    }  
    
    public void playAlbum(Album album) {
        List<Music> albumTracks = new ArrayList<>(album.getMusicas());
        this.currentTracksOrder = albumTracks;
        this.currentTrackIndex = 0;
        this.isPlaying = true;

        System.out.println("\nIniciando reprodução do álbum: " + album.getNome());
        startAlbumPlayback(album);
    }

    public void startAlbumPlayback(Album album) {
        // Initialize the currentTracksOrder with the album's tracks
        this.currentTracksOrder = new ArrayList<>(album.getMusicas());
        this.currentTrackIndex = 0; // Ensure the track index starts at 0
        this.isPlaying = true; // Set the playback state to true

        Scanner controlScanner = new Scanner(System.in);

        while (isPlaying && currentTrackIndex < currentTracksOrder.size()) {
            Music currentMusic = currentTracksOrder.get(currentTrackIndex);
            displayTrackInfo(currentMusic);

            System.out.println("\nControlos: [>] Próxima | [<] Anterior | [S] Sair");

            String command = controlScanner.nextLine().toLowerCase();
            handleUserCommand(command);
        }

        if (currentTrackIndex >= currentTracksOrder.size()) {
            System.out.println("\nFim do álbum " + album.getNome());
        }
    }
    
    public void handleUserCommand(String command) {
        switch (command) {
            case ">" -> nextTrack();
            case "<" -> previousTrack();
            case "r" -> shuffleTrack();
            case "s" -> stopPlayback();
            default -> System.out.println("Comando inválido");
        }
    }
    
    private void displayTrackInfo(Music music) {
        System.out.println("A tocar: " + music.getNome());
        System.out.println("Artista: " + music.getInterprete());
        
        music.reproduzir();
        currentUser.reproduzirMusica();
        currentUser.adicionarMusicaOuvida(music);
    
        System.out.println("\nLetra:");
        String[] linhas = music.getLetra().split("\\n");
        for (String linha : linhas) {
            System.out.println(linha);
        }
    }
    
    public void nextTrack() {
        // Remove a verificação da thread pois não estamos mais usando
        if (currentTrackIndex < currentTracksOrder.size() - 1) {
            currentTrackIndex++;
        } else {
            System.out.println("Última música da playlist");
            isPlaying = false;
        }
    }
    public void previousTrack() {
        if (currentTrackIndex > 0) {
            currentTrackIndex--;
        } else {
            System.out.println("Primeira música da playlist");
        }
    }

public void shuffleTrack() {
    if (currentPlaylist == null || currentPlaylist.getMusics().isEmpty()) {
        System.out.println("Nenhuma playlist em reprodução ou playlist vazia.");
        return;
    }
        
    // Gera um novo índice aleatório diferente do atual
    int newIndex;
    do {
        newIndex = new Random().nextInt(currentPlaylist.getMusics().size());
    } while (newIndex == currentTrackIndex && currentPlaylist.getMusics().size() > 1);
    
    currentTrackIndex = newIndex;
    
    startPlayback();
}
    public void stopPlayback() {
        isPlaying = false;
        if (playbackThread != null) {
            playbackThread.interrupt();
        }
        System.out.println("Reprodução encerrada.");
    }
}
