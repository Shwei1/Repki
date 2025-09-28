public class Arabica extends Coffee {
    
    @Override
    protected double calculatePrice(){
        return weight * 1.548;
    }

    public Arabica(int weight, int strength){
        this.weight = weight;
        this.price = calculatePrice();
        this.strength = strength;
    }

    @Override
    public String toString(){
        return "A Bag of Arabica. Weight: " + weight + ". Price: " + price + ". Stength: " + strength;
    }

}
