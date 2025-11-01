import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

public class B07_02 {

    public static void main(String[] args) throws IOException, ClassNotFoundException{

        int age = Integer.parseInt(args[0]);

        String inp = "input.toys";
        String out = "output.toys";

        Toy[] arr1 = {new Toy("Teddy Bear", 0, 100),
                     new Toy("Rattle", 0, 3),
                     new Toy("Toy Gun", 5, 100),
                     new Toy("LEGO", 6, 14),
                     new Toy("Toy Mortar", 3, 17),
                     new Toy("Yo-Yo", 8, 100),
                     new Toy("Spinning Top", 0, 3)
                    };

        write(arr1, inp);

        Toy[] arr2 = read(inp);

        arr2 = Arrays.stream(arr2).filter(toy ->
                toy.getMinimumAge() <= age &&
                toy.getMaximumAge() >= age).toArray(Toy[]::new);

        
        write(arr2, out);

        System.out.println(Arrays.toString(arr2));
    }

    public static void write(Toy[] arr, String out) throws IOException, ClassNotFoundException {
        var f = new ObjectOutputStream(new FileOutputStream(out));
        for (var t: arr)
            f.writeObject(t);
        f.close();
    }

    public static Toy[] read(String inp) throws IOException, ClassNotFoundException{
        List<Toy> res = new ArrayList<>();
        var f = new ObjectInputStream(new FileInputStream(inp));
        while(true){
            try {
                res.add((Toy) f.readObject());
            } catch (EOFException end){
                break;
            }
        }

        return res.toArray(new Toy[0]);
         
    }
}
