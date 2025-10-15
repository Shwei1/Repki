public class B06_03 {
    public static void main(String[] args){
        String input = args[0];

        input = input.replaceAll("[\\u2212\\p{Pd}]", "-");

        String regex = "(((\\s+)?[+-]?(\\s+)?[0-9]+)((\\s+)?[+-\\/\\*]))+((\\s+)?[+-]?(\\s+)?[0-9]+)(\\s+)?";

        System.out.printf("Expression \"%s\" is valid: %b\n", input, input.matches(regex));
    }
}
