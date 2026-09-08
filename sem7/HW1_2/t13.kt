fun main() {
   val m = readln().toInt()

   when (m) {
      in 1..2, 12 -> println("Winter")
      in 3..5 -> println("Spring")
      in 6..8 -> println("Summer")
      in 9..11 -> println("Autumn")
   }
}
