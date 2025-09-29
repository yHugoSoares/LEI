package src;

import java.util.concurrent.locks.*;



public class Bank {

    private static class Account {
        private Lock lock = new ReentrantLock();
        private int balance;
        
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        
        boolean deposit(int value) {
            lock.lock();
            try {
                balance += value;
                return true;
            } finally {
                lock.unlock();
            }
        }
        boolean withdraw(int value) {
            lock.lock();
            try {
                if (value > balance)
                    return false;
                balance -= value;
                return true;
            } finally {
                lock.unlock();
            }
        }

        void lock() { lock.lock(); }
        void unlock() { lock.unlock(); }
    }

    // Bank slots and vector of accounts
    private int slots;
    private Account[] av; 

    public Bank(int n) {
        slots=n;
        av=new Account[slots];
        for (int i=0; i<slots; i++) av[i]=new Account(0);
    }

    // Account balance
    public int balance(int id) {
        if (id < 0 || id >= slots)
            return 0;
        av[id].lock();
        try {
            return av[id].balance();
        } finally {
            av[id].unlock();
        }
    }

    // Deposit
    public boolean deposit(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        av[id].lock();
        try {
            return av[id].deposit(value);
        } finally {
            av[id].unlock();
        }
    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        av[id].lock();
        try {
            return av[id].withdraw(value);
        } finally {
            av[id].unlock();
        }
    }


    // Transfer; fails if no such account or insufficient balance
    public boolean transfer(int from, int to, int value) {
        if (from < 0 || from >= slots || to < 0 || to >= slots)
            return false;
        if (from == to)
            return true;
        // Lock accounts in a fixed global order to prevent deadlock
        if (from < to) {
            av[from].lock();
            av[to].lock();
        } else {
            av[to].lock();
            av[from].lock();
        }
        try {
            if (av[from].withdraw(value)) {
                av[to].deposit(value);
                return true;
            } else {
                return false;
            }
        } finally {
            av[from].unlock();
            av[to].unlock();
        }
    }

    // Total balance
    public int totalBalance() {
        int total = 0;
        // Lock all accounts in order to prevent deadlock
        for (int i = 0; i < slots; i++) {
            av[i].lock();
            try {
                total += av[i].balance();
            } finally {
                av[i].unlock();
            }
        }
        return total;
    }

}



