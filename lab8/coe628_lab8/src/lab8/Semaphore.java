package lab8;

import java.util.logging.Level;
import java.util.logging.Logger;



public class Semaphore {

    private int value;

    /**
     * Create a semaphore.
     * @param value The initial value of the Semaphore ( must be &ge; 0).
     */
    public Semaphore(int value) {
        this.value = value;
    }
    /**
     * Increment the number of available resources.  This method never blocks.
     * It may wakeup a Thread waiting for the Semaphore. 
     */
    public synchronized void up() throws InterruptedException{
       this.value++;
       if(this.value <= 0){
           notify();
       }
    }
    
    /**
     * Request a resource. If no resources are available, the calling Thread
     * block until a resource controlled by the Semaphore becomes available.
     */
    public synchronized void down() throws InterruptedException{
        this.value--;
        if(this.value < 0){
            wait();
        }
    }

}