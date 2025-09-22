import java.lang.Thread;
import java.lang.Runnable;
import java.lang.InterruptedException;
import java.util.concurrent.locks.*;

class MyThread extends Thread {
    public void run() {
        for (int i = 0; i < 10 ; i++) 
        System.out.println("Thread is running");
    }
}

class MyRunnable implements Runnable {
    public void run() {
        for (int i = 0; i < 10 ; i++) 
        System.out.println("Runnable is running");
    }
}

class Main {
    public static void main(String[] args) throws InterruptedException {
        MyThread t1 = new MyThread();
        // t1.run(); <-- NEVER DO THIS
        t1.start();
        // t1.start(); <-- CANT START MORE THAN ONCE
        
        Runnable r = new MyRunnable();

        Thread t2 = new Thread(r);
        t2.start();
        
        Thread t3 = new Thread(r);
        t3.start();
        
        System.out.println("Main thread is running");
        t1.join();
        System.out.println("END");
    }
}


// EX1

class E1 {
    public static void main(String[] args) throws InterruptedException {
        final int N = 10;
        Thread[] threads = new Thread[N];
        for (int i = 0; i < N; i++) {
            threads[i] = new Thread(new Increment());
            threads[i].start();
        }
        for (int i = 0; i < N; i++) {
            threads[i].join();
        }

        System.out.println("END");
    }
}



// EX2

class Depositor implements Runnable {

    final Bank b;
    final int I;
    final int V;

    public Depositor(Bank b, int I, int V) {
        this.b = b;
        this.I = I;
        this.V = V;
    }

    public void run() {
        for (long i = 0; i < I; i++) {
            b.deposit(V);
            System.out.println("Depositing " + i);
        }
    }
}


class E2 {
    public static void main(String[] args) throws InterruptedException {
        final int N = Integer.parseInt(args[0]);
        final int I = Integer.parseInt(args[1]);
        final int V = Integer.parseInt(args[2]);

        Bank b = new Bank();

        Thread[] threads = new Thread[N];
        for (int i = 0; i < N; i++) {
            threads[i] = new Thread(new Depositor(b, I, V));
            threads[i].start();
        }
        for (int i = 0; i < N; i++) {
            threads[i].join();
        }

        System.out.println("Valor: " + b.balance());
    }
}