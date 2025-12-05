public interface Student {

    public void teachSubject(String type, int credits);

    public void obtainScholarship(int amount);

    public void obtainHelp(int amount);

    public void payCanteen(int amount);

    public void payHostel(int amount);

    public void addMoney(int amount);

    public void addCredits(int amount);

    public void takeMoney(int amount);

    public int getMoney();

    public void setMoney(int amount);

    public void setRequiredCredits(int amount);

    public int getCredits();

    public int getRequiredCredits();

    public void cook();

    public boolean isCooked();
}
