public class CampusDirectorate {
    
    public static void admitStudent(Student student, int price){
        if (student.getMoney() < price){
            DeanOffice.expel(student);
            return;
        }
        student.takeMoney(price);
    }
}
