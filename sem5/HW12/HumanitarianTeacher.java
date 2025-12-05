public class HumanitarianTeacher implements Teacher {

    @Override
    public void teachStudent(Student student, int credits){
        return;
    }
    
    public static void teachStudent(HumanitarianStudent student, int credits){
        student.addCredits(credits);
    }

    public static void teachStudent(NaturalHumanitarianStudent student, int credits){
        student.addCredits(credits);
    }
    
    public static void teachStudent(NaturalStudent student, int credits){
        // System.out.println("Cannot teach natural students!");
        return;
    }
}
