public class Lorry<T> {

    private int load = 0;
    private T[] cargo; 

    private int calculateLoad(){
        int result = 0;
        for (var element: cargo){
            result += element.getWeight();
        }
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

}
