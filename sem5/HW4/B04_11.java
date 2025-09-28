import java.util.Arrays;

public class B04_11 {
    
    public static void main(String[] args){
       

        final Coffee[] carr = {new Arabica(1000, 5), new Liberica(500, 4), new Excelsa(2000, 9), new Robusta(400, 10), new Arabica(5000, 7),
        new Excelsa(5000, 1), new Robusta(30, 9), new Liberica(30, 8)};

        Lorry<Coffee> lorry = new Lorry<Coffee>(carr);

        System.out.println(lorry.getLoad());

        System.out.println(Arrays.toString(lorry.getCargo()));

        lorry.sortCargo();

        System.out.println(Arrays.toString(lorry.getCargo()));
        
        System.out.print("Coffee with strength in interval [5, 8]: ");
        System.out.println(Arrays.toString(lorry.findCargoWithStrengthInInterval(5, 8)));
    }
}
