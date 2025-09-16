import java.util.Scanner;

public class B02_17 {
    
    private static double f(double x){
        final double epsilon = 1e-12;
        double a = 1.0d;
        int k = 0;
        double result = 0;
        double xPow = 1;
        int signum = 1;

        if (Math.abs(x) >= 1.0d)
            throw new IllegalArgumentException("Ряд не збігається для |x|>=1.");

        while(Math.abs(a) > epsilon){
            a = signum * (1+k) * xPow;
            result += a;
            k++;
            signum *= -1;
            xPow *= x;
        }

        return result;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        
        double x = in.nextDouble();

        System.out.println(f(x));
    }
}
