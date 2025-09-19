public class Circle {
    private double x, y;
    private double radius;

    public Circle(double x, double y, double r){
        this.x = x;
        this.y = y;
        this.radius = r;
    }

    public static double euclideanDistance(double x1, double y1, double x2, double y2){
        return Math.sqrt((x1-x2) * (x1-x2) + (y1-y2)*(y1-y2));
    }

    public double perimeter(){
        return Math.PI * 2 * radius;
    }
    
    @Override
    public String toString() {
        return "Circle with centre (" + x + "," + y + ") and radius " + radius;
    }

    public boolean equals(Circle other){
        return x == other.x && y == other.y && radius == other.radius;
    }

    public double area(){
        return Math.PI * radius * radius;
    }

    public static boolean intersection(Circle c1, Circle c2){
        if (euclideanDistance(c1.x, c1.y, c2.x, c2.y) <= c1.radius + c2.radius && Math.abs(c1.radius-c2.radius) <= euclideanDistance(c1.x, c1.y, c2.x, c2.y)){
            return true;
        }
        return false;
    }

    public static void findIntersections(Circle[] carr){
        for (int i = 0; i < carr.length; i++){
            for (int j = i+1; j < carr.length; j++){
                if (intersection(carr[i], carr[j])){
                    System.out.printf("Circle %d intersects Circle %d\n",i, j);
                }
            }
        }
    }

    public static Circle findLargest(Circle[] carr){
        int maxIndex = 0;
        double maxArea = 0;
        for (int i = 0; i < carr.length; i++){
            double currArea = carr[i].area();
            if (currArea > maxArea){
                maxArea = currArea;
                maxIndex = i;
            }
        }
        return carr[maxIndex];
    }

}
