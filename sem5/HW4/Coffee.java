public abstract class Coffee implements Comparable<Coffee>{
    protected double price;
    protected int weight;
    protected int strength;

    protected abstract double calculatePrice();

    public void setWeight(int weight){
        this.weight = weight;
    }

    public void setStrength(int strength){
        this.strength = strength;
    }

    public int getWeight(){
        return weight;
    }

    public int getStrength(){
        return strength;
    }

    public double getPrice(){
        return price;
    }

    @Override 
    public int compareTo(Coffee other){
        return Double.compare(getPrice(), other.getPrice());
    }

    public static Coffee[] findCoffeeWithStrengthInInterval(Coffee[] arr, int a, int b){
        int counter = 0;
        for (var powder: arr){
            if (a <= powder.getStrength() && powder.getStrength() <= b)
                counter++;
        }

        Coffee result[] = new Coffee[counter];
        int idx = 0;
        for (var powder: arr){
            if (a <= powder.getStrength() && powder.getStrength() <= b){
                result[idx] = powder;
                idx++;
            }
        }
        return result;
    }

}
