package utils;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import models.SubscriptionPlans.*;
import models.User;
import models.MusicTypes.*;
import services.DataManager;
import ui.MainMenu;
import validation.UserValidator;


public class Utils {

    public static void seeUsers(DataManager dataManager) {
        List<User> users = dataManager.getUsers();
        if (users.isEmpty()) {
            System.out.println("Nenhum utilizador encontrado.");
        } else {
            System.out.println("\nLista de utilizadores:");
            for (User user : users) {
                System.out.println("- " + user.getNome());
            }
            System.out.println("");
        }
    }

    public static void createUser(DataManager dataManager, Scanner scanner) {
        System.out.print("Indique nome: ");
        String nome = scanner.nextLine();
        if (!UserValidator.validarNome(nome)) {
            System.out.println("Nome inválido.");
            return;
        }
    
        System.out.print("Indique email: ");
        String email = scanner.nextLine();
        if (!UserValidator.validarEmail(email)) {
            System.out.println("Email inválido.");
            return;
        }
    
        System.out.print("Indique morada: ");
        String morada = scanner.nextLine();
        if (!UserValidator.validarMorada(morada)) {
            System.out.println("Morada inválida.");
            return;
        }
    
        System.out.print("Indique plano de subscrição (Free, PremiumBase, PremiumTop): ");
        String planoSubscricao = scanner.nextLine();
        SubscriptionPlan plano;
        switch (planoSubscricao) {
            case "Free", "1" -> plano = new models.SubscriptionPlans.FreePlan();
            case "PremiumBase", "2" -> plano = new models.SubscriptionPlans.PremiumBase();
            case "PremiumTop", "3" -> plano = new models.SubscriptionPlans.PremiumTop();
            default -> {
                System.out.println("Plano inválido.");
                return;
            }
        }
    
        User user = new User(nome, email, morada, plano);
        dataManager.addUser(user);
        if (user != null) {
            try {
                dataManager.saveState("data/app_state.ser");
            } catch (IOException e) {
                System.err.println("Erro ao salvar o estado: " + e.getMessage());
            }
            System.out.println("Conta criada com sucesso. Bem-vindo(a), " + user.getNome());
            new MainMenu(dataManager, user).displayMenu(); 
            return;
        }
    }

    public static void selectUser(DataManager dataManager, Scanner scanner) {
        System.out.print("Indique o seu nome: ");
        String nome = scanner.nextLine();

        List<User> users = dataManager.getUsers();
        for (User user : users) {
            if (user.getNome().equalsIgnoreCase(nome)) {
                System.out.println("Login feito com sucesso! Bem-vindo(a), " + user.getNome());
                MainMenu menu = new MainMenu(dataManager, user);
                menu.displayMenu();
                return;
            }
        }
        System.out.println("Utilizador não encontrado. Tente novamente.");
    }

    public static void removeUser(DataManager dataManager, Scanner scanner) {
        System.out.print("Enter the email of the user to remove: ");
        String email = scanner.nextLine();
        boolean removed = dataManager.removeUserByEmail(email); 
        if (removed) {
            System.out.println("User removed successfully.");
            try {
                dataManager.saveState("data/app_state.ser");
                System.out.println("State saved successfully.");
            } catch (IOException e) {
                System.err.println("Failed to save state: " + e.getMessage());
            }
        } else {
            System.out.println("User not found.");
        }
    }

    public static void saveState(DataManager dataManager) {
        try {
            dataManager.saveState("data/app_state.ser");
            System.out.println("Estado guardado com sucesso.");
        } catch (Exception e) {
            System.err.println("Erro ao guardar o estado: " + e.getMessage());
        }
    }
}
