package ui;

import models.User;
import services.DataManager;
import ui.MainMenu;
import validation.UserValidator;
import models.SubscriptionPlans.*;
import utils.Utils;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;


public class StartMenu {
    private final DataManager dataManager;
    private final Scanner scanner;

    public StartMenu(DataManager dataManager) {
        this.dataManager = dataManager;
        this.scanner = new Scanner(System.in);
    }

    public void start() {
        while (true) {
            System.out.println("\n=== SpotifUM ===");
            Utils.seeUsers(dataManager);
            System.out.println("1. Sign Up (Criar conta)");
            System.out.println("2. Sign In (Entrar)");
            System.out.println("X. Sair");
            System.out.print("Escolha uma opção: ");

            String choice = scanner.nextLine().toUpperCase(); // Convert input to uppercase

            switch (choice) {
                case "1" -> { Utils.createUser(dataManager, scanner); }
                case "2" -> { Utils.selectUser(dataManager, scanner); }
                case "X" -> {
                    System.out.println("Até logo!");
                    return;
                }
                default -> System.out.println("Opção inválida.");
            }
        }
    }
}
