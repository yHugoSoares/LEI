import java.util.Scanner;

public class Ficha3 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Escolha o exercicio: ");
        String opcaoEx = sc.nextLine();

        switch (opcaoEx) {
            case "1" -> {
                Circulo c = new Circulo(1, 1, 2);

                System.out.println("Escolha a alinea: ");
                String opcaoA = sc.nextLine();
                switch (opcaoA) {
                    case "a" -> System.out.println("X:" + c.getX());
                    case "b" -> System.out.println("Y:" + c.getY());
                    case "c" -> System.out.println("Raio:" + c.getRaio());
                    case "d" -> c.alteraCircle(2, 2, 5);
                    case "e" -> c.alteraCentro(3, 3);
                    case "f" -> System.out.println("Area: " + c.calculaArea());
                }
            }
            case "2" -> {
                Sensor s = new Sensor(1);
                
                System.out.println("Escolha a alinea: ");
                String opcaoA = sc.nextLine();
                switch (opcaoA) { 
                    case "a" -> System.out.println("Valor: " + s.setPressao(5) + " " + s.getPressao());
                    case "b" -> System.out.println("Valor: " + s.getPressao());
                }
            }
            case "3" -> {
                Musica m = new Musica("505", "Erica", "Artic Monkeys", new String[0], new String[0], 0, 0);

                System.out.println("Escolha a alinea: ");
                String opcaoA = sc.nextLine();
                switch (opcaoA) {
                    case "a" -> System.out.println("Linhas: " + m.qtsLinhasPoema());
                    case "b" -> System.out.println("Caracteres: " + m.numeroCarateres());
                    
                    case "d" -> System.out.println("Linha mais longa: " + m.linhaMaisLonga());

                }
            }
            default -> {
            }
        }
    }
}
