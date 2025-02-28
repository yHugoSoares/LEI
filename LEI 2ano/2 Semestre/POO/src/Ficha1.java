import java.util.Scanner;

public class Ficha1 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Exercicios ex = new Exercicios();

        System.out.println("Escolha o exercicio:");
        String opcao = sc.nextLine();

        switch (opcao) {
            case "1":
                System.out.println("Insira a temperatura em celsius:");
                double celsius = sc.nextDouble();
                System.out.println("A temperatura em farenheit é: " + ex.celsiusParaFarenheit(celsius));
                break;

            case "2":
                System.out.println("Insira o primeiro número:");
                int a = sc.nextInt();
                System.out.println("Insira o segundo número:");
                int b = sc.nextInt();
                System.out.println("O maior número é: " + ex.maximoNumeros(a, b));
                break;

            case "3":
                System.out.println("Insira o nome:");
                String nome = sc.nextLine();
                System.out.println("Insira o saldo:");
                double saldo = sc.nextDouble();
                System.out.println(ex.criaDescricaoConta(nome, saldo));
                break;

            case "4":
                System.out.println("Insira o valor em euros:");
                double valor = sc.nextDouble();
                System.out.println("Insira a taxa de conversão:");
                double taxaConversao = sc.nextDouble();
                System.out.println("O valor em libras é: " + ex.eurosParaLibras(valor, taxaConversao));
                break;

            case "5":
                System.out.println("Insira o primero número:");
                int num1 = sc.nextInt();
                System.out.println("Insira o segundo número:");
                int num2 = sc.nextInt();
                System.out.println("Os números por ordem decrescente são: " + ex.maximoNumeros(num1, num2) + ex.minimoNumeros(num1, num2));
                System.out.println("A média é: " + ex.media(num1, num2));
                break;
            case "6":
                System.out.println("Insira o número:");
                int num = sc.nextInt();
                System.out.println("O factorial é: " + ex.factorial(num));
                break;
            default:
                break;
        }
    }
}

class Exercicios {

    public double celsiusParaFarenheit(double celsius) {
        return (celsius * 9 / 5) + 32;
    }

    public int maximoNumeros(int a, int b) {
        if (a > b) {
            return a;
        } else {
            return b;
        }
    }

    public int minimoNumeros(int a, int b) {
        if (a < b) {
            return a;
        } else {
            return b;
        }
    }

    public String criaDescricaoConta(String nome, double saldo) {
        return "Nome: " + nome + "\nSaldo: " + saldo;
    }

    public double eurosParaLibras(double valor, double taxaConversao) {
        return valor * taxaConversao;
    }

    public int media(int num1, int num2) {
        return (num1 + num2) / 2;
    }

    public long factorial(int num) {
        long factorial = 1;
        for (int i = 1; i <= num; i++) {
            factorial *= i;
        }
        return factorial;
    }
}