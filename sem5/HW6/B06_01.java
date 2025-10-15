import java.time.LocalDate;

public class B06_01 {
    public static void main(String[] args){
        String input = args[0];

        System.out.printf("Received input: %s\n", input);

        String date = LocalDate.now().toString();

        date = date.replaceAll("-", ".");

        String result = input.replaceAll("(([0-9]){2}|(_){2})\\.(([0-9]){2}|(_){2})\\.(([0-9]){4}|(_){4})", date);

        System.out.println(result);
    }
}
