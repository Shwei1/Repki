import java.util.Scanner;

public class B02_07 {

    private static double mean(int[] arr){
        int sum = 0;
        for (int i = 0; i < arr.length; i++){
            sum += arr[i];
        }

        return sum/arr.length;
    }

    private static double[] variance(int[] arr){
        double mean = mean(arr);

        double[] result = new double[arr.length];

        for (int i = 0; i < arr.length; i++){
            result[i] = Math.abs(mean - arr[i]);
        }

        return result;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        
        String line = in.nextLine();

        String[] inputs = line.trim().split("\\s+");

        int[] arr = new int[inputs.length];

        for (int i = 0; i < inputs.length; i++){
            arr[i] = Integer.parseInt(inputs[i]);
        }

        double[] result = variance(arr);

        for (int i = 0; i < arr.length; i++){
            if (i>0) System.out.print(", ");
            System.out.print(result[i]);
        }
        System.out.print("\n");
    }
}
