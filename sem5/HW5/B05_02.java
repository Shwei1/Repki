public class B05_02 {

    private static boolean criterionA(String str){
        char c = str.charAt(0);

        if (!Character.isDigit(c))
            return false;

        int num = Character.getNumericValue(c);

        if (num == 0)
            return false;

        int counter = 0;
        for (int i = 1; i < str.length(); i++){
            char curr = str.charAt(i);
            if (Character.isLetter(curr) && counter < num)
                counter++;
            else
                return false;
        }
        
        return counter == num;
    }

    private static boolean criterionB(String str){
        boolean found = false;
        int num = 0;

        for (int i = 0; i < str.length(); i++){
            char curr = str.charAt(i);

            if (Character.isDigit(curr) && found)
                return false;

            if (Character.isDigit(curr)){
                found = true;
                num = Character.getNumericValue(curr);
            }
        }

        return found && num == str.length();
    }

    private static boolean criterionC(String str){
        int sum = 0;

        for (int i = 0; i < str.length(); i++){
            char curr = str.charAt(i);
            if (Character.isDigit(curr))
                sum += Character.getNumericValue(curr);
        }

        return sum == str.length();
    }



    public static void main(String[] args){
        String input = args[0];

        System.out.println(criterionA(input) ? "Condition A is satisfied" :
                "Condition A is not satisfied");

        System.out.println(criterionB(input) ? "Condition B is satisfied" : 
                "Condition B is not satisfied");
        
        System.out.println(criterionC(input) ? "Condition C is satisfied" : 
                "Condition C is not satisfied");
    }
}
