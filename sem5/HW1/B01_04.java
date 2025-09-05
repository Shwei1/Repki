import java.util.Scanner;

public class B01_04 {
    
    public static double geoMean(int[] arr){
        int result = 1;
        for (int i = 0; i < arr.length; i++){
            result *= arr[i];
        }
        return Math.pow(result, 1.0/arr.length);

    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();

        System.out.printf("%.4f\n", geoMean(new int[]{a, b, c}));

        in.close();

    }

}
