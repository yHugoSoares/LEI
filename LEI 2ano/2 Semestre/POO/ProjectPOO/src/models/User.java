package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import models.MusicTypes.Music;
import models.PlaylistTypes.Playlist;
import models.SubscriptionPlans.*;

public class User implements Serializable {
    private String nome;
    private String email;
    private String morada;
    private SubscriptionPlan planoSubscricao;
    private double pontos; // Change to double
    private List<Playlist> biblioteca_pessoal_p = new ArrayList<>();
    private List<Music> musicasOuvidas = new ArrayList<>();
    private List<Album> biblioteca_pessoal_a = new ArrayList<>();




    // Constructor
    public User(String nome, String email, String morada, SubscriptionPlan planoSubscricao) {
        this.nome = nome;
        this.email = email;
        this.morada = morada;
        this.planoSubscricao = planoSubscricao;
        this.pontos = planoSubscricao.getMembershipBonus(); // No cast needed
    }

    // Getters
    public String getNome() { return nome; }
    public String getEmail() { return email; }
    public String getMorada() { return morada; }
    public SubscriptionPlan getPlanoSubscricao() { return planoSubscricao; }
    public double getPontos() { return pontos; } // Update return type
    public List<Playlist> getPlaylists() { return biblioteca_pessoal_p; }
    public List<Album> getAlbuns() { return biblioteca_pessoal_a; }
    public void addPlaylist(Playlist p) { biblioteca_pessoal_p.add(p); }
    public void addAlbum(Album a) { biblioteca_pessoal_a.add(a); }
    public void removeAlbum(Album a) { biblioteca_pessoal_a.remove(a); }
    public void removePlaylist(Playlist p) { biblioteca_pessoal_p.remove(p); }    
    public List<Music> getMusicasOuvidas() { return new ArrayList<>(musicasOuvidas);}
    


    
    // Setters
    public void setMorada(String morada) { this.morada = morada; }
    public void setPlanoSubscricao(SubscriptionPlan novoPlano) { this.planoSubscricao = novoPlano; }

    // Method
    public void reproduzirMusica() {
        this.pontos += planoSubscricao.calculatePlayPoints(this.pontos); // Use SubscriptionPlan method
    }

    public void adicionarMusicaOuvida(Music musica) {
        this.musicasOuvidas.add(musica);
    }
    
    public int getTempoTotalOuvido() {
        return musicasOuvidas.stream()
                .mapToInt(Music::getDuracao)
                .sum();
    }

    public List<Music> getHistoricoOrdenado() {
        Map<Music, Long> contagem = musicasOuvidas.stream()
            .collect(Collectors.groupingBy(m -> m, Collectors.counting()));
    
        return contagem.entrySet().stream()
            .sorted(Map.Entry.<Music, Long>comparingByValue().reversed())
            .map(Map.Entry::getKey)
            .collect(Collectors.toList());
    }
    

    @Override
    public String toString() {
        return "User{" +
                "nome='" + nome + '\'' +
                ", email='" + email + '\'' +
                ", morada='" + morada + '\'' +
                ", planoSubscricao='" + planoSubscricao.getPlanName() + '\'' +
                ", pontos=" + pontos +
                '}';
    }

    @Override
    public User clone() {
        try {
            User cloned = (User) super.clone();
            return cloned;
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true; 
        if (o == null || getClass() != o.getClass()) return false; 

        User user = (User) o; 

        return email.equals(user.email) &&
               nome.equals(user.nome) &&
               morada.equals(user.morada) &&
               planoSubscricao.equals(user.planoSubscricao);
    }

}
