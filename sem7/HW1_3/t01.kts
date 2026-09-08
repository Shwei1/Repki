fun slowMultiply(a: Int, b: Int): Int {
    var res = 0
    repeat(b) {
        res += a
    }
    return res
}

val a = readln().toInt()
val b = readln().toInt()

println(slowMultiply(a, b))
