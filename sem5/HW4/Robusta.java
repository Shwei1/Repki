public class Robusta extends Coffee {
    
    @Override
    protected double calculatePrice(){
        return weight * 4.201;
    }

    public Robusta(int weight, int strength){
        this.weight = weight;
        this.price = calculatePrice();
        this.strength = strength;
    }

    @Override
    public String toString(){
        return "A Bag of Robusta. Weight: " + weight + ". Price: " + price + ". Stength: " + strength;
    }

}
