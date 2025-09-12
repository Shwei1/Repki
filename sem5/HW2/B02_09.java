import java.util.Scanner;

public class B02_09 {

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);

        byte n = in.nextByte();

// У Java байт також signed, тому для тестування прикладу з n=130 треба вписувати -3.

        byte mask = (byte) (n >>> 7);

        n <<= 1;

        n ^= mask;

        System.out.println((int) n);
    }
}
