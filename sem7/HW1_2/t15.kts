import kotlin.math.sqrt

fun isPrime(n: Long): Boolean {
    for (i in 2L..sqrt(n.toDouble()).toLong()) {
        if (n % i == 0L) {
            return false
        }
    }
    return true
}

var testVec = listOf(2, 3, 4, 6, 10, 11, 19, 911, 3819106237)

for (test in testVec) {
    println("$test is prime: ${isPrime(test)}")
}
