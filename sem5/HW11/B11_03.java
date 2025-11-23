import java.net.http.*;
import java.net.URI;
import java.net.URLEncoder;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

import java.util.regex.*;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class B11_03 {
    
    public static void main(String[] args){
        final String site = "https://godinnik.com/time/" + URLEncoder.encode("київ", StandardCharsets.UTF_8) + "/";
        String html = getHTML(site);
        String remoteTime = getTime(html);

        //System.out.println(html);

        LocalTime localTime = LocalTime.now();
        String parsedTime = localTime.format(DateTimeFormatter.ofPattern("HH:mm:ss"));
        //System.out.println(parsedTime.length() + " " + remoteTime.length());
        System.out.printf("Server time in Kyiv: %s\nLocal time in Kyiv: %s\nEqual? %b\n", remoteTime, parsedTime,
                remoteTime.equals(parsedTime));
    }

    public static String getHTML(String url){
        URI uri = URI.create(url);
        try (HttpClient client = HttpClient.newHttpClient()){
            HttpRequest request = HttpRequest.newBuilder(uri)
                .GET()
                .header("user-agent", "java")
                .build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            System.out.println("Status code: " + response.statusCode());
            return response.body();
        } catch (InterruptedException | IOException e){
            e.printStackTrace();
            return "";
        }
    }

    public static String getTime(String html){
        Pattern p = Pattern.compile(
                "([0-9]+:[0-9]+:[0-9]+)"
                );
        Matcher m = p.matcher(html);

        if (m.find()){
            return m.group(1).trim();
        }

        return "";
    }
}
