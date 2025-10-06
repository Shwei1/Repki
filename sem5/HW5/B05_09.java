import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

record Country(String name, int area, String continent){}

public class B05_09 {

    public static void findCountriesWithAreaNotGreaterThanGiven(String ifile,
                                                    String ofile, int area){
        FileReader fr = new FileReader(ifile);
        FileWriter fw = new FileWriter(ofile);
        PrintWriter pw = new PrintWriter(fw);
        Scanner sc = new Scanner(fr);

        ArrayList<Country> result = new ArrayList<Country>();

        while (sc.hasNextLine()) {
            String name = sc.next();
            int curr_area = sc.nextInt();
            String continent = sc.next();
            
            if (curr_area <= area)
                result.add(new Country(name, curr_area, continent));
        }

        pw.print(result);
        fr.close();
        sc.close();
        fw.close();
        pw.close();
    }

    public static void countCountriesInContinents(String ifile, String ofile){

        FileReader fr = new FileReader(ifile);
        FileWriter fw = new FileWriter(ofile);
        PrintWriter pw = new PrintWriter(fw);
        Scanner sc = new Scanner(fr);

        Map<String, Integer> counts = new HashMap<>();

        while (sc.hasNextLine()) {
            String name = sc.next();
            int area = sc.nextInt();
            String continent = sc.next();

            counts.put(continent, counts.getOrDefault(continent, 0) + 1);
        }
        
        pw.print(counts);
        fr.close();
        sc.close();
        fw.close();
        pw.close();
    }

    public static void main(String[] args){

         findCountriesWithAreaNotGreaterThanGiven(
                 "B05_09-input.txt", "B05_09-output1.txt", 600000
                 );

         countCountriesInContinents("B05_09-input.txt", "B05_09-output2.txt");
    }
}
