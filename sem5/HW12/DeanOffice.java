public class DeanOffice {

    public static void expel(Student student){
        student.cook();
    }

    public static boolean canGraduate(Student student){
        if (student.isCooked()) return false;
        if (student.getRequiredCredits() > student.getCredits()) return false;
        return true;
    }
}
