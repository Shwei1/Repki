import java.util.Scanner;
import java.io.PrintWriter;
import java.util.concurrent.ArrayBlockingQueue;
import java.io.FileNotFoundException;
import java.io.File;
import java.io.IOException;

public class B09_01 {

    private static ArrayBlockingQueue<String> queue1 = new ArrayBlockingQueue<>(12);
    private static ArrayBlockingQueue<String> queue2 = new ArrayBlockingQueue<>(12);
    private static long start = System.currentTimeMillis();
    private static final String EOF = "__EOF__";

    public static void main(String[] args) throws InterruptedException, IOException {
        long T1 = 2000;
        long T2 = 3000;
        long T3 = 5000;

        Thread th1 = new Thread(() -> readFromFile("F.txt", T1));
        th1.setName("ReaderThread");
        Thread th2 = new Thread(() -> writeToFile("B09_01-output", T2, queue1));
        th2.setName("WriterThread1");
        Thread th3 = new Thread(() -> writeToFile("B09_01-output", T3, queue2));
        th3.setName("WriterThread2");

        th1.start();
        th2.start();
        th3.start();

        th1.join();
        th2.join();
        th3.join();
    }
    

    public static void readFromFile(String fileName, long time) {
        try {
            try (Scanner sc = new Scanner(new File(fileName))) {
                while (sc.hasNextLine()) {
                    Thread.sleep(time);
                    String msg = sc.nextLine();
                    queue1.put(msg);
                    queue2.put(msg);
                }
                queue1.put(EOF);
                queue2.put(EOF);
            } catch (FileNotFoundException e){
                e.printStackTrace();
            }
        } catch ( InterruptedException e){
            e.printStackTrace();
        }
    }


    public static void writeToFile(String fileName, long time, ArrayBlockingQueue<String> queue){
        try {
        
            String newFileName = fileName + "_" + Thread.currentThread().getName() + ".txt";
            File of = new File(newFileName);
            of.createNewFile();
            PrintWriter writer = new PrintWriter(newFileName, "UTF-8");

            while (true){
                String msg = queue.take();
                if (msg.equals(EOF)) break;
                System.out.println("Took message: " + msg);
                writer.printf("[%6.2f]: %s\n", 
                        (System.currentTimeMillis() - start) / 1000.0, 
                        msg);
                Thread.sleep(time);
                writer.flush();
            }
            writer.close();
        } catch (IOException | InterruptedException e){
            e.printStackTrace();
        }  
    }
}
