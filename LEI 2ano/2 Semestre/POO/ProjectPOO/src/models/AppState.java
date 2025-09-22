package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import models.MusicTypes.*;
import models.PlaylistTypes.Playlist;

public class AppState implements Serializable {
    private List<User> users = new ArrayList<>();
    private List<Music> songs = new ArrayList<>();
    private List<Playlist> playlists = new ArrayList<>();

    // Getters and setters
    public List<User> getUsers() { return users; }
    public List<Music> getSongs() { return songs; }
    public List<Playlist> getPlaylists() { return playlists; }
}