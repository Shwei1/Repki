public class B01_03 {

    public static void main(String[] args){
        double res = 1.0;
        for (int i = 0; i < args.length; i++){
            try {
                double num = Double.parseDouble(args[i]);
                res *= num;
            }
            catch (NumberFormatException e){
                System.out.println("Неправильні дані проігноровані");
            }
        }
        System.out.println(res);
    }
}
