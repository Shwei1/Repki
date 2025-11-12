import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

class Log {
    public static long start = System.currentTimeMillis();

    public static void print(String msg){
        System.out.printf("[%.2f %s]: %s\n", 
                (System.currentTimeMillis() - start) / 1000.0,
                Thread.currentThread().getName(),
                msg
                );
    }
}

public class B09_08 {

    public static final int N = 8; // amount of cooks
    public static final int M = 8; // amount of customers
    public static final AtomicInteger servedInTime = new AtomicInteger();

    public static void main(String[] args) throws InterruptedException{

        System.out.println("Cooks available: " + N);

        long T1 = 1000;
        long T2 = 2000;
        long T3 = 3000;
        long T4 = 4000;
        long T5 = 3500;

        Semaphore lock = new Semaphore(N);

        Thread[] customers = new Thread[M];

        for (int i = 0; i < M; i++){
            long arriveTime = (long) (Math.random() * (T2-T1) + T1);
            long cookingTime = (long) (Math.random() * (T4-T3) + T3);

            int j = i;

            customers[i] = new Thread(() -> serve(j, arriveTime, cookingTime, T5, lock));
            customers[i].start();
        }

        for (int i = 0; i < M; i++){
            customers[i].join();
        }

        System.out.printf("Total customers: %d, served in time: %d\n", M, servedInTime.get());
    }

    public static void serve(int i, long arriveTime, long cookingTime, long waitingTreshold, Semaphore lock){
        Thread.currentThread().setName("Customer " + i);
        try {
            Thread.sleep(arriveTime);
            long startedWaiting = System.currentTimeMillis();
            Log.print(" has arrived");
            lock.acquire();
            long finishedWaiting = System.currentTimeMillis();
            Log.print(" order brought to the cook");
            Thread.sleep(cookingTime);
            lock.release();
            Log.print(" has been served");
            if (finishedWaiting - startedWaiting < waitingTreshold) servedInTime.incrementAndGet();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }
}
