package src;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barrier {

    private final int N;
    private int count = 0;
    private int generation = 0;
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition allReached = lock.newCondition();

    Barrier(int N) {
        this.N = N;
    }

    void await() throws InterruptedException {
        lock.lock();
        try {
            int currentGeneration = generation;
            count++;
            if (count < N) {
                while (currentGeneration == generation) {
                    allReached.await();
                }
            } else {
                count = 0;
                generation++;
                allReached.signalAll();
            }
        } finally {
            lock.unlock();
        }
    }
}
