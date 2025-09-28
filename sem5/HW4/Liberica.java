public class Liberica extends Coffee {

    @Override
    protected double calculatePrice(){
       return weight * 0.979;
    }

    public Liberica(int weight, int strength){
        this.weight = weight;
        this.price = calculatePrice();
        this.strength = strength;
    }

    @Override
    public String toString(){
        return "A Bag of Liberica. Weight: " + weight + ". Price: " + price + ". Stength: " + strength;
    }

}
