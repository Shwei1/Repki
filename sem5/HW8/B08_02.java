import java.util.Deque;
import java.util.ArrayDeque;

public class B08_02 {

    public static boolean validate(String input){
        Deque<Character> stk = new ArrayDeque<>();

        for (int i = 0; i < input.length(); i++){
            char c = input.charAt(i);
            switch (c) {
                case '(':
                    stk.addFirst(c);
                    break;
                case ')':
                    if (stk.isEmpty() || stk.peekFirst() != '(')
                        return false;
                    else
                        stk.removeFirst();
                    break;
                case '{':
                    stk.addFirst(c);
                    break;
                case '}':
                    if (stk.isEmpty() || stk.peekFirst() != '{')
                        return false;
                    else
                        stk.removeFirst();
                    break;
                case '[':
                    stk.addFirst(c);
                    break;
                case ']':
                    if (stk.isEmpty() || stk.peekFirst() != '[')
                        return false;
                    else
                        stk.removeFirst();
                    break;
                default:
                    break;

            }
        }
        return stk.isEmpty();
    }
    
    public static void main(String[] args){
        String input = args[0];

        System.out.println("Is string \"" + input + "\" valid: " + validate(input));
    }
}
