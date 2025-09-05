import java.util.Scanner;

public class B01_05 {
    
    public static void main(String[] args){
        int N, M;
        if (args.length > 0){
            N = Integer.parseInt(args[0]);
            M = Integer.parseInt(args[1]);
        }
        else {
            Scanner in = new Scanner(System.in);
            N = in.nextInt();
            M = in.nextInt();
            in.close();
        }

        for (int i = 0; i < N; i++){
            System.out.println((int) (Math.random() * M));
        }

    }

}
