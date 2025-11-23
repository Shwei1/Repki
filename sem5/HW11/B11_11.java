import java.util.Map;
import java.util.LinkedHashMap;

import java.net.URI;
import java.net.http.*;
import java.io.IOException;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

import java.time.LocalDate;

public class B11_07 {

    public static void main(String[] args){
        String cityName = args[0];

        String url = "https://www.timeanddate.com/weather/ukraine/" + cityName + "/";

        String html = getHTML(url);

        //System.out.println(html);
        var forecast = parseForecast(html);

        System.out.println("Сьогодні " + LocalDate.now());

        System.out.println("Прогноз погоди у місті " + cityName + " на два тижні:");

        for (Map.Entry<String, String> entry: forecast.entrySet())
            System.out.println(entry.getKey() + ": " + entry.getValue());
    }

    public static String getHTML(String url){
        URI uri = URI.create(url);
        try (HttpClient client = HttpClient.newBuilder()
                .followRedirects(HttpClient.Redirect.ALWAYS)
                .build()){

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

        Pattern p = Pattern.compile("</span>.*?<div .*?>(?<day0>.*?)</div>.*?<p>(?<max0>.*?) / (?<min0>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day1>.*?)</div>.*?<p>(?<max1>.*?) / (?<min1>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day2>.*?)</div>.*?<p>(?<max2>.*?) / (?<min2>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day3>.*?)</div>.*?<p>(?<max3>.*?) / (?<min3>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day4>.*?)</div>.*?<p>(?<max4>.*?) / (?<min4>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day5>.*?)</div>.*?<p>(?<max5>.*?) / (?<min5>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day6>.*?)</div>.*?<p>(?<max6>.*?) / (?<min6>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day7>.*?)</div>.*?<p>(?<max7>.*?) / (?<min7>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day8>.*?)</div>.*?<p>(?<max8>.*?) / (?<min8>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day9>.*?)</div>.*?<p>(?<max9>.*?) / (?<min9>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day10>.*?)</div>.*?<p>(?<max10>.*?) / (?<min10>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day11>.*?)</div>.*?<p>(?<max11>.*?) / (?<min11>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day12>.*?)</div>.*?<p>(?<max12>.*?) / (?<min12>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day13>.*?)</div>.*?<p>(?<max13>.*?) / (?<min13>.*?)&nbsp;°C</p>.*?" + 
                "<div .*?>(?<day14>.*?)</div>.*?<p>(?<max14>.*?) / (?<min14>.*?)&nbsp;°C</p>.*?");

        Matcher m = p.matcher(html);

        if (m.find()){
            for (int i = 0; i <= 14; i++)
                forecast.put(m.group("day" + i),
                        "максимум — " + m.group("max" + i) + ", " +
                        "мінімум — " + m.group("min" + i));
        } else {
            System.out.println("Nothing found");
        }

        return forecast;
    }

}
