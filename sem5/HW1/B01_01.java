import java.util.Scanner;
public class B01_01 {
    public static void main(String[] args){
        System.out.println("Введіть ім'я: ");
        Scanner in = new Scanner(System.in);
        
        String name = in.next();

        System.out.printf("Привіт, %s!\n", name);

        in.close();

    }  
    

}
