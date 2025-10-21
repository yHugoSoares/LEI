import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class Warehouse {
    private Map<String, Product> map =  new HashMap<String, Product>();
    private ReentrantLock lock = new ReentrantLock();

    private class Product { int quantity = 0; }

    private Product get(String item) {
        Product p = map.get(item);
        if (p != null) return p;
        p = new Product();
        map.put(item, p);
        return p;
    }

    public void supply(String item, int quantity) throws  InterruptedException {
        lock.lock();
        try {
            Product p = get(item);
            p.quantity += quantity;
        } finally {
            lock.unlock();
        }
    }


    public void consume(Set<String> items) throws InterruptedException {
        lock.lock();
        try {
            for (String s : items) {

                if (get(s).quantity > 0) {
                    get(s).quantity--;
                    continue;
                }
                throw new IllegalStateException("Item " + s + " is out of stock");
            }
            
        } finally {
            lock.unlock();
        }
    }














    
    /**
    void await() throws InterruptedException {
        lock.lock();
        try {
            Instance my = current;
            my.counter++;
            while (current == my) {
                c.await();
            }
            else {
                c.signalAll();
                current = new Instance();
            }
        } finally {
            lock.unlock();
        }
    }
    */
    



}
