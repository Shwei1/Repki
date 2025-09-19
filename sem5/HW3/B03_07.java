import java.util.Arrays;

public class B03_07 {

    public static void main(String[] args){
        final int circleCount = 10;
        
        Circle[] carr = new Circle[circleCount];

        for (int i = 0; i < circleCount; i++){
            double x = Math.random() * 10;
            double y = Math.random() * 10;
            double r = Math.random() * 10;
            carr[i] = new Circle(x, y, r);
            System.out.println("New circle with area " + carr[i].area());
        }

        Circle.findIntersections(carr);
        System.out.println(Arrays.toString(carr));
        System.out.println("The largest circle is: " + Circle.findLargest(carr).toString());
    }
}

