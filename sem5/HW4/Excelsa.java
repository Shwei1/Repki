public class Excelsa extends Coffee {
    
    @Override
    private double calculatePrice(){
        return weight * 2.050;
    }

    public Excelsa(int weight, int strength){
        this.weight = weight;
        this.price = calculatePrice();
        this.strength = strength;
    }

    @Override
    public String toString(){
        return "A Bag of Excelsa. Weight: " + weight + ". Price: " + price + ". Stength: " + strength;
    }

}
