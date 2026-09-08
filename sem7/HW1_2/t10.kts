// eolymp 5054

fun isLeapYear(year: Int): Boolean {
    val isLeap = 
        ((year % 100 != 0) &&
        (year % 4 == 0)) ||
        (year % 400 == 0)
    return isLeap
}

fun main() {
    val year = readln().toInt()
    println(if (isLeapYear(year)) "YES" else "NO")
}
