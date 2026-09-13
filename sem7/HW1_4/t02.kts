println("== Normal class ==")

run {
    
    class Employee(var firstName: String, var secondName: String, var position: String)

    val emp1 = Employee("John", "Blaire", "Boss")
    val emp2 = Employee("John", "Blaire", "Boss")
    val emp3 = emp1

    // T02$Employee@3ea1729e, Employee не має перевантаженого toString()
    println("$emp1")

    // Хиба, бо це посилання на різні об'єкти
    println("By reference ${emp1 === emp2}")

    // Хиба, бо без перевантаженого equals() використовується те саме порівняння
    // по посиланню
    println("By value ${emp1 == emp3}")

}

println("== Data class ==")

run {
    data class Employee(var firstName: String, var secondName: String, var position: String) {
        var bonus: Int = 0
    }

    val emp1 = Employee("John", "Blaire", "Boss")
    val emp2 = Employee("John", "Blaire", "Boss")
    val emp3 = emp1

    println("By value ${emp1 == emp3}")

    val (name, surname, position) = emp1
    println("Worker: $name $surname, $position")

    val emp4 = emp2.copy(position = "Janitor")
    println("$emp4")

    val emp5 = Employee("Robert", "Wright", "Accountant")
    emp5.bonus = 100

    val emp6 = Employee("Robert", "Wright", "Accountant")
    emp6.bonus = 200

    println("Different bonuses yield equality: ${emp5 == emp6}")
}

println("== Custom dataclass ==")

run {
    class Employee(var firstName: String, var secondName: String, var position: String) {

        override fun toString(): String {
            return "Employee(firstName=$firstName, secondName=$secondName, position=$position)"
        }

        operator fun component1(): String = firstName

        operator fun component2(): String = secondName

        operator fun component3(): String = position

        fun copy(
            firstName: String = this.firstName,
            secondName: String = this.secondName,
            position: String = this.position
        ): Employee {
            return Employee(firstName, secondName, position)
        }
    }

    val emp1 = Employee("John", "Blaire", "Boss")
    val emp2 = Employee("John", "Blaire", "Boss")
    val emp3 = emp1

    println("By value ${emp1 == emp3}")

    val (name, surname, position) = emp1
    println("Worker: $name $surname, $position")

    val emp4 = emp2.copy(position = "Janitor")
    println("$emp4")

    
}                 

