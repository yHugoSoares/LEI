import java.util.Random;
import src.Bank;


public class BankTest {

    private static class Mover implements Runnable {
        private Bank b;
        private int accs;
        private int iters;

        public Mover(Bank b, int accs, int iters) {
            this.b = b;
            this.accs = accs;
            this.iters = iters;
        }

        public void run() {
            Random rand = new Random();
            for (int m = 0; m < iters; m++) {
                int from = rand.nextInt(accs);
                int to = rand.nextInt(accs);
                b.transfer(from, to, 1);
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int ACCS = 10;
        int ITERS = 100000;
        Bank b = new Bank(ACCS);
        for (int i = 0; i < ACCS; i++)
            b.deposit(i, 1000);
        int balance1 = b.totalBalance();
        System.out.println(balance1);

        Thread t1 = new Thread(new Mover(b, ACCS, ITERS)); 
        Thread t2 = new Thread(new Mover(b, ACCS, ITERS));
        t1.start();
        t2.start();
        t1.join();
        t2.join();

        int balance2 = b.totalBalance();
        System.out.println(balance2);
        if (balance1 != balance2)
            System.out.println("Unexpected balance");
        else
            System.out.println("Test OK");


        // Additional test cases
        System.out.println();
        System.out.println("Running additional test cases...");

        Bank bFail = new Bank(1);
        bFail.deposit(0, 1000);
        boolean resultFail = bFail.withdraw(0, 2000); // Should fail, not enough balance
        int balanceFail = bFail.balance(0);

        // This assertion will fail: it expects the balance to be 0, but it should be 1000
        if (balanceFail != 0) { 
            System.out.println("Unexpected balance after failed withdrawal: " + balanceFail);
        }
        // This assertion will also fail: it expects the withdrawal to succeed
        if (!resultFail) {
            System.out.println("Test failed: Withdrawal should have succeeded");
        }
        else { System.out.println("Test passed"); }
    }

}
