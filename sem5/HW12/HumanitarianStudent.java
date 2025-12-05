public class HumanitarianStudent implements Student {

    private int money;
    private int requiredCredits;
    private int credits = 0;
    private boolean cooked = false;

    public HumanitarianStudent(){}; 
    
    @Override
    public void teachSubject(String type, int credits){
        if (type.equals("humanitarian")){
            HumanitarianTeacher.teachStudent(this, credits);
        }
        else if (type.equals("natural")){
            NaturalTeacher.teachStudent(this, credits);
        }
    }

    @Override
    public void obtainScholarship(int amount){
        BookkeepingOffice.payScholarship(this, amount);
    }

    @Override 
    public void obtainHelp(int amount){
        Parent.payChild(this, amount);
    }

    @Override
    public void payCanteen(int amount){
        Canteen.serveStudent(this, amount);
    }

    @Override
    public void payHostel(int amount){
        CampusDirectorate.admitStudent(this, amount);
    }

    @Override
    public void addCredits(int amount){
        this.credits += amount;
    }
    
    @Override
    public void addMoney(int amount){
        this.money += amount;
    }

    @Override
    public void takeMoney(int amount){
        this.money -= amount;
    }

    @Override
    public int getMoney(){
        return money;
    }
    
    @Override
    public int getRequiredCredits(){
        return requiredCredits;
    }
    
    @Override
    public int getCredits(){
        return credits;
    }

    @Override
    public void cook(){
        this.cooked = true;
    }

    @Override
    public boolean isCooked(){
        return this.cooked;
    }
    
    @Override
    public void setRequiredCredits(int amount){
        this.requiredCredits = amount;
    }
    
    @Override
    public void setMoney(int amount){
        this.money = amount;
    }
}
