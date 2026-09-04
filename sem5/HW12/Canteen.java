public class Canteen {

    public static void serveStudent(Student student, int price){
        if (student.getMoney() < price){
            DeanOffice.expel(student);
            return;
        }
        student.takeMoney(price);
    }
}
