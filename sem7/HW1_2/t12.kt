fun foo1(x: Long): Long = 
3 * x * x * x + 4 * x * x + 5 * x + 6

fun foo2(x: Long): Long =
3 * x * x * x - 2 * x * x - 3 * x - 4

fun main() {
   val x = readln().toLong()
   println(if (x >= 13) foo1(x) else foo2(x))
}
