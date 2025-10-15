import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class B06_02 {
    public static void main(String[] args){
        String input = args[0];

        System.out.printf("Received input: %s\n", args[0]);

        String regex = "(?!.*--)(\\+)?(-)?([0-9]+)(\\([0-9]+\\))?([0-9]|-)+(?<!-)";
        
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(input);

        System.out.println("Found phone numbers:\n");

        while (matcher.find()){
            System.out.println(matcher.group());
        }

        System.out.println();

    }
}
