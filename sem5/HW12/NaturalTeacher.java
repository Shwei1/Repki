public class NaturalTeacher implements Teacher {
    
    @Override 
    public void teachStudent(Student student, int credits){
        return;
    }

    public static void teachStudent(NaturalStudent student, int credits){
        student.addCredits(credits);
    }

    public static void teachStudent(NaturalHumanitarianStudent student, int credits){
        student.addCredits(credits);
    }

    public static void teachStudent(HumanitarianStudent student, int credits){
        //System.out.println("Cannot teach humanitarian students!");
        return;
    }
}
