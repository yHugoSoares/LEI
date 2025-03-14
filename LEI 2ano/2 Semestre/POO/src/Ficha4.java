import java.util.Scanner;

public class Ficha4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Escolha o exercicio: ");
        String opcaoEx = sc.nextLine();

        switch (opcaoEx) {
            case "1" -> {
                Stack stack = new Stack();
                System.out.println("Stack criada com sucesso!");
                stack.push("Eu sou lindo!");
                stack.push("Eu sou feio!");
                stack.push("Eu sou bonito!");
                stack.push("Eu sou feio!");
                stack.push("Eu sou lindo!");
                stack.push("Eu sou feio!");
                System.out.println("Stack: " + stack.toString());

            }
        }
    }
}
