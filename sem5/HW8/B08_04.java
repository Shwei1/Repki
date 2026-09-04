import java.util.PriorityQueue;
import java.util.Arrays;

class Point {
    public double x;
    public double y;

    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString(){
        return "(" + x + ", " + y + ")";
    }
}

public class B08_04 {

    public static double euclidianDistance(Point p1, Point p2){
        return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    public static double euclidianDistance(Point p){
        return Math.sqrt(p.x * p.x + p.y * p.y);

    }

    public static void main(String[] args){
        
        PriorityQueue<Point> pq = new PriorityQueue<>(
                (p1, p2) -> Double.compare(euclidianDistance(p1), euclidianDistance(p2))
                );

        Point[] arr = {new Point(0, 0), new Point(500, 100), new Point(1.0, -0.4), new Point(15, 20), new Point(-12.04, -50)};

        System.out.println("Unsorted points: " + Arrays.toString(arr));

        for (var p: arr){
            pq.add(p);
        }

        while (!pq.isEmpty()){
            System.out.println(pq.poll());
        }
    } 
}
