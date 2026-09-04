import java.net.ServerSocket;
import java.net.Socket;

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;

import java.io.File;
import java.io.FileNotFoundException;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

import java.nio.charset.StandardCharsets;

public class B10_07_Server {

    public static File inFile = new File("F.txt");

    public static ArrayList<Integer> findLineNumbers(String query){
        ArrayList<Integer> result = new ArrayList<>();
        int i = 1;
        try (Scanner sc = new Scanner(inFile)){
            while (sc.hasNextLine()){
                String line = sc.nextLine().trim();

                line = line.toLowerCase().replaceAll("[,\\.:;]", "");
                
                List<String> words = Arrays.asList(line.split("\\s+"));

                if (words.contains(query))
                    result.add(i);
                i++;
            }
        } catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        final int port = 14123;

        try (ServerSocket server = new ServerSocket(port)){
           while (true) {
               Socket conn = server.accept();

               var reader = new BufferedReader(
                       new InputStreamReader(
                           conn.getInputStream(), StandardCharsets.UTF_8
                           )
                       );

               var writer = new PrintStream(
                       conn.getOutputStream(), true, StandardCharsets.UTF_8
                       );

               while (true) {
                   String query = reader.readLine();
                   if (query == null) break;
                   var ans = findLineNumbers(query);

                   writer.println(ans.toString());
               }
           }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
