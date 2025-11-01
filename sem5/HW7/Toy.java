import java.io.Serializable;

public class Toy implements Serializable {
    private static final long serialVersionUID = 1L;

    private String name;
    private double price;
    private int minimumAge;
    private int maximumAge;

    public Toy(String name, double price, int minimumAge, int maximumAge){
        this.name = name;
        this.price = price;
        this.minimumAge = minimumAge;
        this.maximumAge = maximumAge;
    }


    public Toy(String name, int minimumAge, int maximumAge){
        this.name = name;
        this.price = Double.NaN;
        this.minimumAge = minimumAge;
        this.maximumAge = maximumAge;
    }

    public String getName(){
        return name;
    }

    public double getPrice(){
        return price;
    }

    public int getMinimumAge(){
        return minimumAge;
    }

    public int getMaximumAge(){
        return maximumAge;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setMinimumAge(int age){
        this.minimumAge = age;
    }

     public void setMaximumAge(int age){
        this.maximumAge = age;
    }

    public void setPrice(double price){
        this.price = price;
    }
    
    @Override
    public String toString(){
        return name + " (" + minimumAge + ", " + maximumAge + ")";
    }

}
