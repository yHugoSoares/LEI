package services;

import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import utils.*;
import models.MusicTypes.*;
import models.PlaylistTypes.Playlist;
import models.*;

public class DataManager implements Serializable { // Implement Serializable
    private static final long serialVersionUID = 1L; // Add serialVersionUID
    private List<User> users;
    private List<Music> musics;
    private List<Playlist> playlistsPublicas;
    private List<Album> albuns;
    private AppState appState; // Add AppState

    public DataManager() {
        this.users = new ArrayList<>();
        this.musics = new ArrayList<>();
        this.playlistsPublicas = new ArrayList<>();
        if (this.appState == null) {
            this.appState = new AppState();
        }
        this.albuns = new ArrayList<>();
        this.appState = new AppState(); // Initialize AppState
    }

    public void loadMusicFromCSV(String filePath) {
        List<Music> importedMusic = CSVImporter.importMusicFromCSV(filePath);
        this.musics.addAll(importedMusic);
        System.out.println(importedMusic.size() + " músicas importadas do CSV.");
    }

    public void inicializarMusicas() {
        if (musics == null) {
            musics = new ArrayList<>();
        }
        
        // Add Multimedia music with the required "multimedia" parameter
        musics.add(new Multimedia("Shape of You", "Ed Sheeran", "Atlantic", "Letra...", 
                                 new String[]{"C", "G", "Am", "F"}, "Pop", 233, "Video"));
        
        // Add Explicit music with the required "explicit" parameter
        musics.add(new Explicit("Bohemian Rhapsody", "Queen", "EMI", "Letra...",
                                 new String[]{"G", "Bb", "C", "D"}, "Rock", 355, 1));

        // Add another Explicit music with the required "explicit" parameter
        musics.add(new Explicit("We Will Rock You", "Queen", "EMI", "Letra...",
                                 new String[]{"D", "G", "C"}, "Rock", 122, 1));
        
        // Add another Multimedia music with the required "multimedia" parameter
        musics.add(new Multimedia("Someone Like You", "Adele", "XL", "Letra...",
                                 new String[]{"A", "E", "F#m", "D"}, "Pop", 285, "Live Performance"));
        
        // Normal music
        musics.add(new BaseMusic("Let It Be", "The Beatles", "Apple Records", "Let it be, let it be...", 
                                 new String[]{"C", "G", "Am", "F"}, "Rock", 243));

        // Multimedia music
        musics.add(new Multimedia("Blinding Lights", "The Weeknd", "Republic", "Letra...", 
                                 new String[]{"F#m", "C#m", "E", "D"}, "Synthpop", 200, "Music Video"));

        // Explicit music
        musics.add(new Explicit("Rap God", "Eminem", "Shady Records", "Letra...", 
                                 new String[]{"Em", "G", "D", "C"}, "Rap", 364, 2));

        // Normal music
        musics.add(new BaseMusic("Thinking Out Loud", "Ed Sheeran", "Asylum", "Letra...", 
                                 new String[]{"D", "G", "A", "Bm"}, "Pop", 281));

        // Multimedia music
        musics.add(new Multimedia("Smells Like Teen Spirit", "Nirvana", "DGC", "Letra...", 
                                 new String[]{"F", "B♭", "A♭", "D♯"}, "Grunge", 301, "Live Video"));

        // Explicit music
        musics.add(new Explicit("SICKO MODE", "Travis Scott", "Cactus Jack", "Letra...", 
                                 new String[]{"C", "D", "E", "F"}, "Hip-Hop", 312, 1));

        
    }

    public void inicializarAlbuns() {
        if (albuns == null) {
            albuns = new ArrayList<>();
        }
    
        // Check if albums are already initialized
        if (!albuns.isEmpty()) {
            System.out.println("Álbuns já foram inicializados.");
            return;
        }
    
        if (musics == null || musics.size() < 4) {
            System.out.println("Músicas insuficientes para criar álbuns.");
            return;
        }
    
        // Álbum 1
        Album queenHits = new Album("Queen Greatest Hits", "Queen", "EMI", "1981", "Rock", true);
        queenHits.addAlbum(musics.get(1)); // Bohemian Rhapsody
        queenHits.addAlbum(musics.get(2)); // We Will Rock You
    
        // Álbum 2
        Album edSheeranLove = new Album("Love Songs", "Ed Sheeran", "Atlantic", "2014", "Pop", true);
        edSheeranLove.addAlbum(musics.get(0)); // Shape of You
        edSheeranLove.addAlbum(musics.get(6)); // Thinking Out Loud
    
        // Álbum 3
        Album mixRock = new Album("Classic Rock", "Vários", "Universal", "1990", "Rock", false);
        mixRock.addAlbum(musics.get(4)); // Let It Be
        mixRock.addAlbum(musics.get(8)); // Smells Like Teen Spirit
    
        albuns.add(queenHits);
        albuns.add(edSheeranLove);
        albuns.add(mixRock);
    
        System.out.println("Álbuns iniciais criados.");
    }
        
    public List<Album> getAlbuns() {
        return albuns;
    }
    

    public void addUser(User user) {
        users.add(user);
    }

    public boolean removeUserByEmail(String email) {
        Iterator<User> iterator = users.iterator();
        while (iterator.hasNext()) {
            User user = iterator.next();
            if (user.getEmail().equals(email)) {
                iterator.remove();
                return true; 
            }
        }
        return false; 
    }

    public void saveState(String filename) throws IOException {
        if (this.playlistsPublicas == null) this.playlistsPublicas = new ArrayList<>();
        if (this.users == null) this.users = new ArrayList<>();
        if (this.musics == null) this.musics = new ArrayList<>();
        
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(this);
        }
    }

    public static DataManager loadState(String filename) throws IOException, ClassNotFoundException {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            return (DataManager) ois.readObject();
        }
    }

    public List<User> getUsers() {
        return users;
    }

    public List<Music> getMusics() { 
        return this.musics; 
    }
    
    public void addMusic(Music music) {
        this.musics.add(music);
    }
    

    public AppState getAppState() {
        return appState;
    }

    public void setAppState(AppState appState) {
        this.appState = appState;
    }

    public List<Playlist> getPlaylistsPublicas() {
        return playlistsPublicas;
    }
    
    public void adicionarPlaylistPublica(Playlist playlist) {
        if (playlist == null) {
            throw new IllegalArgumentException("Playlist não pode ser nula");
        }
        if (!playlist.isPublica()) {
            throw new IllegalArgumentException("Só playlists públicas podem ser adicionadas aqui");
        }
        if (this.playlistsPublicas == null) {
            this.playlistsPublicas = new ArrayList<>(); // Initialize if null
        }
        playlistsPublicas.add(playlist);
    }
}
