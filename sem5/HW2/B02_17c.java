import java.util.Scanner;

public class B02_17 {
    
    private static double f(double x){
        final double epsilon = 1e-12;
        double a = 1.0d;
        int k = 0;
        double result = 0;

        while(Math.abs(a) > epsilon){
            a = Math.pow(-1, k) * (1+k) * Math.pow(x, k);
            result += a;
            k++;
        }

        return result;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        
        double x = in.nextDouble();

        System.out.println(f(x));
    }
}
