import java.math.BigInteger

fun factorial(n: Int): BigInteger {
   var res = BigInteger("1")
   for (i in 2..n) {
      res *= i.toBigInteger()
   }
   return res
}

fun main() {
   val n = readln().toInt()
   println(factorial(n))
}

// fun factorial(n: Long): Long {
//    var res = 1L
//    for (i in 2..n) {
//       res *= i
//    }
//    return res
// }

// fun main() {
//    val n = readln().toLong()
//    println(factorial(n))
// }
