package validation;

import models.User;
import models.SubscriptionPlans.SubscriptionPlan;

import java.util.regex.Pattern;

public class UserValidator {
    
    // Expressão regular para validar emails
    private static final Pattern EMAIL_PATTERN = 
        Pattern.compile("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$");

    // Lista de planos válidos
    private static final String[] PLANOS_VALIDOS = {"Free", "PremiumBase", "PremiumTop"};

    // Valida nome (não pode ser vazio)
    public static boolean validarNome(String nome) {
        return nome != null && !nome.trim().isEmpty();
    }

    // Valida email usando regex
    public static boolean validarEmail(String email) {
        return email != null && EMAIL_PATTERN.matcher(email).matches();
    }

    // Valida morada (não pode ser vazia)
    public static boolean validarMorada(String morada) {
        return morada != null && !morada.trim().isEmpty();
    }

    // Valida se o plano de subscrição é um dos permitidos
    public static boolean validarPlano(SubscriptionPlan plano) {
        for (String p : PLANOS_VALIDOS) {
            if (p.equals(plano.getPlanName())) return true; // Validate using planName
        }
        return false;
    }

    // Método principal para validar um utilizador inteiro
    public static boolean validarUtilizador(User utilizador) {
        return validarNome(utilizador.getNome()) &&
               validarEmail(utilizador.getEmail()) &&
               validarMorada(utilizador.getMorada()) &&
               validarPlano(utilizador.getPlanoSubscricao());
    }
}

