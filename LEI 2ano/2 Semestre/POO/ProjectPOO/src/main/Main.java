package main;

import java.io.IOException;
import models.AppState;
import services.DataManager;
import ui.StartMenu;

public class Main {
    public static void main(String[] args) {
        DataManager dataManager;
        AppState appState;

        try {
            dataManager = DataManager.loadState("data/app_state.ser"); // Load existing data
            appState = dataManager.getAppState();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("No saved state found. Starting fresh.");
            dataManager = new DataManager();
            appState = new AppState();
            dataManager.setAppState(appState);
        }

        // Lançar o menu inicial (Sign in / Sign up)
        StartMenu startMenu = new StartMenu(dataManager);
        startMenu.start();

        try {
            dataManager.saveState("data/app_state.ser");
        } catch (IOException e) {
            System.err.println("Failed to save state: " + e.getMessage());
        }
    }
}
