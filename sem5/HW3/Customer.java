import java.util.Arrays;

public class Customer implements Comparable<Customer> {
    private String name;
    private String address;
    private int creditCardNumber;
    private int bankAccountNumber;

    public Customer(String name, String address, int creditCardNumber, int bankAccountNumber){
        this.name = name;
        this.address = address;
        this.creditCardNumber = creditCardNumber;
        this.bankAccountNumber = bankAccountNumber;
    }

    public Customer(Customer other){
        name = other.name;
        address = other.address;
        creditCardNumber = other.creditCardNumber;
        bankAccountNumber = other.bankAccountNumber;
    }

    public String getName(){
        return name;
    }

    public String getAddress(){
        return address;
    }

    public int getCreditCardNumber(){
        return creditCardNumber;
    }

    public int getBankAccountNumber(){
        return bankAccountNumber;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setAddress(String address){
        this.address = address;
    }

    public void setCreditCardNumber(int n){
        this.creditCardNumber = n;
    }

    public void setBankAccountNumber(int n){
        this.bankAccountNumber = n;
    }

    @Override
    public String toString(){
        return "Customer: " + name + " " + address + " " + creditCardNumber + " " + bankAccountNumber;
    }

    public boolean equals(Customer other){
        return name == other.name && address == other.address
            && creditCardNumber == other.creditCardNumber 
            && bankAccountNumber == other.bankAccountNumber;
    }
    
    @Override
    public int compareTo(Customer other){
        return getName().compareTo(other.getName());
    }

    public static void sortCustomers(Customer[] carr){
        Arrays.sort(carr);
    }

    
    public static Customer[] getCustomersWithCreditCardNumbersInInterval(Customer[] carr, int a, int b) {
        int count = 0;
        for (Customer c : carr) {
            if (c.getCreditCardNumber() >= a && c.getCreditCardNumber() <= b) {
                count++;
            }
        }

        Customer[] result = new Customer[count];

        int idx = 0;
        for (Customer c : carr) {
            if (c.getCreditCardNumber() >= a && c.getCreditCardNumber() <= b) {
                result[idx++] = c;
            }
        }

        return result;
    }
}
