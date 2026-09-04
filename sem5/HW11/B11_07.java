import java.util.Map;
import java.util.LinkedHashMap;

import java.net.URI;
import java.net.http.*;
import java.io.IOException;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class B11_07 {

    public static void main(String[] args){
        String cityName = args[0];

        // 301: moved permanently (на домен .com)
        String url = "https://www.meteoprog.com/ua/weather/" + cityName + "/";

        String html = getHTML(url);
        var forecast = parseForecast(html);
        System.out.println("Прогноз погоди на сьогодні та наступні 4 дні:");
        for (Map.Entry<String, String> entry: forecast.entrySet())
            System.out.println(entry.getKey() + ": " + entry.getValue());
    }

    public static String getHTML(String url){
        URI uri = URI.create(url);
        try (HttpClient client = HttpClient.newHttpClient()){
            HttpRequest request = HttpRequest.newBuilder(uri)
                .GET()
                .header("user-agent", "java")
                .build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            return response.body();
        } catch (InterruptedException | IOException e){
            e.printStackTrace();
            return "";
        }
    }

    public static Map<String, String> parseForecast(String html){
        Map<String, String> forecast = new LinkedHashMap<>();
          
        Pattern p = Pattern.compile("<section class=\"weather-day-by-day-slider\">(?s).*?<h4>Сьогодні</h4>.*?<span>(?<day0>.*?)</span>.*?<h4>(?<max0>.*?)</h4>.*?<h4>(?<min0>.*?)</h4>.*?<span>(?<day1>.*?)</span>.*?<h4>(?<max1>.*?)</h4>.*?<h4>(?<min1>.*?)</h4>.*?<span>(?<day2>.*?)</span>.*?<h4>(?<max2>.*?)</h4>.*?<h4>(?<min2>.*?)</h4>.*?<span>(?<day3>.*?)</span>.*?<h4>(?<max3>.*?)</h4>.*?<h4>(?<min3>.*?)</h4>.*?<span>(?<day4>.*?)</span>.*?<h4>(?<max4>.*?)</h4>.*?<h4>(?<min4>.*?)</h4>", Pattern.DOTALL);

        Matcher m = p.matcher(html);
        
        if (m.find()){
            for (int i = 0; i <= 4; i++)
                forecast.put(m.group("day" + i),
                        "максимум — " + m.group("min" + i) + ", " +
                        "мінімум — " + m.group("max" + i));
            /*
             * На сайті мінімум з максимумом переплутані
             */
        }

        return forecast;
    }

}
