import kotlin.math.sqrt

fun absValue(real: Double = 0.0, imag: Double = 0.0): Double =
    sqrt(real * real + imag * imag)

println("|2| = ${absValue(2.0)}")
println("|-2| = ${absValue(-2.0)}")
println("|-2.5| = ${absValue(-2.5)}")
println("|1 + i| = ${absValue(1.0, 1.0)}")
println("|i| = ${absValue(imag = 1.0)}")
