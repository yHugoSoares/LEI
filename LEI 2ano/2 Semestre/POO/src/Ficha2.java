import java.time.LocalDate;
import java.util.Arrays;
import java.util.Scanner;

public class Ficha2 {

    public static int[] addToArray(Scanner sc) {
        System.out.println("Choose the array size: ");
        int size = sc.nextInt();
        int[] array = new int[size];
        for (int i = 0; i < size; i++) {
            System.out.println("Insert the " + (i+1) + " number: ");
            int number = sc.nextInt();
            array[i] = number;
        }
        return array;
    }

    public void insereData(LocalDate data) {
        System.out.println("Data: " + data);

        
    }

    // public static void printArray(int[] array) {
    //     String result = "";
    //     for (int i = 0; i < array.length; i++) {
    //         result += array[i] + " ";
    //     }
    //     System.out.println(result);
    // }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Exercicios ex = new Exercicios();
        
        System.out.println("Choose an exercise: ");
        int exercise = sc.nextInt();

        switch (exercise) {
            case 1 -> {
                // a
                int[] array1 = addToArray(sc);
                System.out.println("The minimum number is: " + ex.min(array1));
                
                // b
                System.out.println("Insert the first index: ");
                int a = sc.nextInt();
                System.out.println("Insert the second index: ");
                int b = sc.nextInt();
                System.out.println(Arrays.toString(ex.inBetween(array1, a, b)));
                
                // c
                int[] array2 = addToArray(sc);
                System.out.println(Arrays.toString(ex.commonElements(array1, array2)));
            }
            case 2 -> {
            }
            case 3 -> {
            }
            case 4 -> {
            }
        }
    }
}

class Exercicios {
    
    public int min(int[] array) {
        int min = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] < min) {
                min = array[i];
            }
        }
        return min;
    }

    public int[] inBetween(int[] array, int a, int b) {
        int size = Math.abs(b - a) + 1;
        int[] newArray = new int[size];
        int counter = 0;
        if (a < 0 || b < 0 || a >= array.length || b >= array.length) {
            return null;
        }
        else if (a <= b) {
            for (int i = a; i <= b; i++) {
                newArray[counter++] = array[i];
            }
        }
        else if (a > b) {
            for (int i = b; i <= a; i++) {
                newArray[counter++] = array[i];
            }
        }
        else return null;
        
        return newArray;
    }

    public int[] commonElements(int[] array1, int[] array2) {
        int size = 0;
        for (int i = 0; i < array1.length; i++) {
            for (int j = 0; j < array2.length; j++) {
                if (array1[i] == array2[j]) {
                    size++;
                }
            }
        }
        int[] newArray = new int[size];
        int counter = 0;
        for (int i = 0; i < array1.length; i++) {
            for (int j = 0; j < array2.length; j++) {
                if (array1[i] == array2[j]) {
                    newArray[counter++] = array1[i];
                }
            }
        }
        return newArray;
    }

    public LocalDate dataMaisProxima(LocalDate data) {
        return ;
    }

}