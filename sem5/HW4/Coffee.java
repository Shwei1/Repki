public class Coffee extends Beverage{
    protected int caffeineAmount;
    
    public int getCaffeineAmount(){
        return caffeineAmount;
    }

    public void setCaffeineAmount(int amount){
        caffeineAmount = amount;
    }

    @Override
    public String toString(){
        return "Coffee with caffeine amount of " + caffeineAmount + 
            " and price " + super.getPrice();
    }

}
