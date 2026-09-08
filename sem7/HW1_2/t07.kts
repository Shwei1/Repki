import kotlin.math.PI

fun circleArea(r: Int): Double {
    return PI * r * r
}

fun circleAreaSmall(r: Int): Double = PI * r * r

println(circleArea(2))
println(circleAreaSmall(2))
