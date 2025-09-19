import java.util.Arrays;

public class B03_09 {

    public static void main(String[] args){
        Customer c1 = new Customer("Zubenko Valeriy Albertovych",
                                "A street", 1000, 15);
        Customer c2 = new Customer("Zhi Quangxi Lee", "B street", 1500, 16);

        Customer c3 = new Customer("Potuzhny Evhen Mykolayovych", "C street", 2000, 17);

        Customer c4 = new Customer("Borman Volodymyr Borysovych", "C++ street", 1750, 18);

        Customer[] carr = {c3, c2, c4, c1};

        System.out.println(Arrays.toString(carr));

        Customer.sortCustomers(carr);

        System.out.println(Arrays.toString(carr));

        System.out.println("Customers with card numbers in range [1001, 1999]: " + Arrays.toString(Customer.getCustomersWithCreditCardNumbersInInterval(carr, 1001, 1999)));
    }
}
