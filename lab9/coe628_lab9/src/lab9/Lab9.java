/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

/**
 *
 * @author aasamaro
 */

import java.util.*;
import java.io.*;

public class Lab9 {
    
    public static final int N = 5; //Number of philosophers at the table
    public enum state_t {EATING, THINKING, HUNGRY};
    public static Philosopher[] philosophers;
    public static Semaphore forks; 
    public static int count = 0;
    
    public static void main(String args[]){
        
        forks = new Semaphore(N);
        philosophers = new Philosopher[N];
        
        //Initialize the Philosophers
        for(int i = 0; i < N; i++){
            philosophers[i] = new Philosopher();
        }
        
        //Start each Philosopher
        for(int i = 0; i < N; i++){
            philosophers[i].start();
        }
        
        while(count >= N){
            try{
                for(int i = 0; i < N; i++){
                    philosophers[i].join();
                }
            }catch(Exception ex){
                System.out.println("Exception");
            }
            System.out.println("All Philosophers have eaten.");
        }
        
    }

    
    public static class Philosopher extends Thread{
        
        private static int M_ID = 0;
        private int id = 0; //Philosopher ID
        private state_t state;
        private int leftN, rightN; //Left and Right neighbour
        
        public Philosopher(){
            this.id = M_ID;
            M_ID++;
            state = state_t.HUNGRY;
            if(this.id == 0){
                rightN = 1;
                leftN = N-1;
            }
            else if(this.id == (N-1)){
                rightN = 0;
                leftN = N-2;
            } else {
                rightN = this.id + 1;
                leftN = this.id - 1;
            }
    }
        
    @Override
    public String toString(){
        
        return "Phil: "+ this.id + " State: " + this.state.toString();
        
    }
    
    public synchronized void thinking(){
        
        this.state = state_t.THINKING;
        System.out.println(this.toString());
        
        try{
            wait(10);
        }catch(Exception ex){
            System.out.println("Thinking Exception.");
        }
    }
    
    public synchronized void eating(){
        
    
        this.state = state_t.EATING;
        System.out.println(this.toString());
        
        try{
            Thread.sleep(15);
        }catch(Exception ex){
            System.out.println("Eating Exception.");
        }
    }
    
    public synchronized void takeForks(){
        
        System.out.println(this.toString());
        System.out.println("Attempting to get Forks...\n");
        
        while(philosophers[leftN].getState_t() == state_t.EATING || philosophers[rightN].getState_t() == state_t.EATING){
            
            System.out.println(this.id + "'s fork is in use.\n");
            thinking();
        }
        
        if(philosophers[leftN].getState_t() != state_t.EATING || philosophers[rightN].getState_t() != state_t.EATING){
            
            try{
                forks.down();
            }catch(InterruptedException ie){
                System.out.println("Take Fork Exception.\n");
            }
            
            this.state = state_t.EATING;
            System.out.println(this.id + "'s Fork is acquired.\n");
        }
    }
    
    public synchronized void putForks(){
        
        this.state = state_t.THINKING;
        
        try{
            forks.up();
        }catch(InterruptedException ie){
            System.out.println("Put Fork Error");
        }
        
        count++;
        }
    
    public state_t getState_t(){
        return this.state;
    }
    
    @Override
    public void run(){
        thinking();
        takeForks();
        eating();
        putForks();
        System.out.println(this.toString());
    }
   
    }
}
