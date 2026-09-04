import java.util.Scanner;
import java.util.ArrayList;

import java.net.Socket;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;

import java.nio.charset.StandardCharsets;

public class B10_07_Client {

    public static void main(String[] args) throws IOException {
        
        final int port = 14123;
        final String host = "localhost";
        
        Socket sock = new Socket(host, port);

        var reader = new BufferedReader(
                new InputStreamReader(
                    sock.getInputStream(), StandardCharsets.UTF_8
                    )
                );


        var writer = new PrintStream(
                sock.getOutputStream(), true, StandardCharsets.UTF_8
                );

        Scanner sc = new Scanner(System.in);
        
        while (true) {
            try {
                String query = sc.next();
                writer.println(query);
                String response = reader.readLine();
                System.out.println("Server found " + query + " on lines:" + response);
            } catch (Exception e){
                sock.close();
                e.printStackTrace();
            }
        }
    }
}
