public class B05_01 {

    private static boolean checkValid(String str){
        int open = 0;
        for (int i = 0; i < str.length(); i++){
            char c = str.charAt(i);
            if (c == '(')
                open++;
            else if (c == ')'){
                open--;
                if (open < 0) 
                    return false;
            }
        }
        return open == 0;
    }

    private static String clearString(String str){
        String prev;
        do {
            prev = str;
            str = str.replaceAll("\\([^()]*\\)", "");
        } while(!str.equals(prev));

        return str;
    }

    public static void main(String[] args){
        String input = args[0];
        if (!checkValid(input))
            throw new IllegalArgumentException("Input string is invalid!");
        
        String result = clearString(input);

        System.out.println(result);
    }

}
