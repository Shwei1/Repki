public class B04_11 {
    
    public static void main(String[] args){
       

        final Coffee[] carr = {new Arabica(1000, 5), new Liberica(500, 4), new Excelsa(2000, 9)};
        Lorry<Coffee> lorry = new Lorry(carr);

        System.out.println(lorry.getLoad());

        System.out.println(lorry.getCargo());

        lorry.sortCargo();

        System.out.println(lorry.getCargo());
    }
}
