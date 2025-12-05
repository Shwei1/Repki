import java.util.Scanner;
import java.util.Arrays;
import java.io.File;

public class B12_01 {
    public static void main(String[] args){
        for (int i = 1; i <= 14; i++){
            String fileName = "";
            if (i < 10)
                fileName = "input0" + i + ".txt";
            else
                fileName = "input" + i + ".txt";
        
            try (Scanner sc = new Scanner(new File(fileName))){
                Student s = new HumanitarianStudent();
                String type = sc.nextLine();
                type = type.replaceAll("\\s", "");
                switch (type) {
                    case "humanitarian":
                        s = new HumanitarianStudent();
                        break;
                    case "natural":
                        s = new NaturalStudent();
                        break;
                    case "natural-humanitarian":
                        s = new NaturalHumanitarianStudent();
                        break;
                    default:
                        break;
                }
                int requiredCredits = Integer.parseInt(sc.nextLine().replaceAll("\\s", ""));
                int startMoney = Integer.parseInt(sc.nextLine().replaceAll("\\s", ""));
                s.setRequiredCredits(requiredCredits);
                s.setMoney(startMoney);
                
                while (sc.hasNextLine()){
                    if (s.isCooked()){
                        break;
                    }

                    String[] command = sc.nextLine().trim().split("\\s+");
                    if (command[0].equals("obtain")){
                        if (command[1].equals("help")){
                            int amount = Integer.parseInt(command[2]);
                            s.obtainHelp(amount);
                        }
                        else if (command[1].equals("scholarship")){
                            int amount = Integer.parseInt(command[2]);
                            s.obtainScholarship(amount);
                        }
                        else
                            System.out.println("Wrong input format. Need obtain + help/scholarship, got " + command[1]);
                    }
                    else if (command[0].equals("teach")){
                        s.teachSubject(command[1], Integer.parseInt(command[2]));
                    }
                    else if (command[0].equals("pay")){
                        if (command[1].equals("canteen")){
                            int amount = Integer.parseInt(command[2]);
                            s.payCanteen(amount);
                        }
                        else if (command[1].equals("hostel")){
                            int amount = Integer.parseInt(command[2]);
                            s.payHostel(amount);
                        }
                    }
                    else {
                        System.out.println("Author is cooked. Command was: " + Arrays.toString(command));
                    }
                }

                if (DeanOffice.canGraduate(s)){
                    System.out.println("Student " + i + " graduated successfully");
                    //System.out.printf("He had %d credits and required %d\n", s.getCredits(), s.getRequiredCredits());
                    //System.out.printf("He ended up with %d UAH\n", s.getMoney());
                }
                
                else
                    System.out.println("Student " + i + " is COOKED and cannot graduate!");
                    //System.out.printf("He had %d credits and required %d\n", s.getCredits(), s.getRequiredCredits());
                    //System.out.printf("He ended up with %d UAH\n", s.getMoney());

            } catch (Exception e){
                e.printStackTrace();
            }
        } 
    }
}
