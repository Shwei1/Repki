import java.util.Arrays;

public class Lorry<T extends Coffee> {

    private int load = 0;
    private T[] cargo; 

    private int calculateLoad(){
        int result = 0;
        for (var element: cargo){
            result += element.getWeight();
        }
        return result;
    }

    public Lorry(T[] arr){
        cargo = arr;
        load = calculateLoad();
    }

    public int getLoad(){
        return load;
    }

    public T[] getCargo(){
        return cargo;
    }

    public void sortCargo(){
        Arrays.sort(cargo);
    }

    public Coffee[] findCargoWithStrengthInInterval(int a, int b){
        return Coffee.findCoffeeWithStrengthInInterval(cargo, a, b);
    } 
}
