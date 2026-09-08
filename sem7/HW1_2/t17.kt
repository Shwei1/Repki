fun reverseNum(n: Long): Long {
   var nMut = n
   var base = 1L
   var res = 0L
   while (nMut > 0) {
      res *= 10
      val digit = nMut % 10
      res += digit   
      nMut /= 10
   }
   return res
}

fun main() {
   val n = readln().toLong()
   println(reverseNum(n))
}
