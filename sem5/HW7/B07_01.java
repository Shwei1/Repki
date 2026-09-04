import java.io.*;
import java.util.Arrays;

public class B07_01 {

    public static void main(String[] args) throws IOException{
        
        double a = Double.parseDouble(args[0]);

        String inp = "./F";
        String out = "./G";

        double[] arr1 = {1.5, 1.7, 0.08, 100.901, 4.195, 501.1, -0.800008, 9000.1};

        write(arr1, inp);

        double[] arr2 = read(inp);

        arr2 = Arrays.stream(arr2).filter(x -> x > a).toArray();

        write(arr2, out);

        System.out.println(Arrays.toString(arr2));
    }
    
    public static void write(double[] arr, String out) throws IOException{
        var f = new DataOutputStream(new FileOutputStream(out));
        for (double x: arr)
            f.writeDouble(x);
        f.close();
    }

    public static double[] read(String inp) throws IOException{
        
        var f = new DataInputStream(new FileInputStream(inp));

        int size = (int) new File(inp).length() / Double.BYTES;

        double[] arr = new double[size];

        for (int i = 0; i < size; i++)
            arr[i] = f.readDouble();

        return arr;
    }
}
