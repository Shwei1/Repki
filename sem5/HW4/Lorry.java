public class Lorry<T> {

    private double load = 0;
    private T[] cargo; 

    public Lorry(T[] arr){
        cargo = arr;
    }

}
