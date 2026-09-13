import kotlin.random.Random

sealed interface Roots

data class TwoRoots(val x1: Double, val x2: Double) : Roots
data class OneRoot(val x: Double) : Roots
data object ZeroRoots : Roots


class QuadraticEquation(a: Double, var b: Double, var c: Double) {
    init {
        require(a != 0.0) { "The first coefficient may not be zero!" }
    }

    var a: Double = a
    set(value) {
        require(value != 0.0) { "The first coefficient may not be zero!" }
        field = value
    }

    constructor(a: Int, b: Int, c: Int) : this(a.toDouble(), b.toDouble(), c.toDouble())

    constructor(b: Double, c: Double) : this(1.0, b, c)

    override fun toString(): String {
        return "${a}x^2 + ${b}x + $c = 0"
    }

    val discriminant: Double
    get() = b * b - 4 * a * c

    
    fun solve() : Roots {
        val d = discriminant
        return when {
            d > 0 -> {
                val sqrtD = kotlin.math.sqrt(d)
                TwoRoots((-b + sqrtD) / (2 * a), (-b - sqrtD) / (2 * a))
            }
            d == 0.0 -> OneRoot(-b / (2 * a))
            else -> ZeroRoots
        }
    }
}

fun randomNonZero(): Int {
    var value: Int
    do {
        value = Random.nextInt(-50, 51)
    } while (value == 0)
    return value
}

val equations = List(100) {
    QuadraticEquation(
        randomNonZero(),
        Random.nextInt(-50, 51),
        Random.nextInt(-50, 51)
    )
}

equations
    .map { it to it.solve() }
    .filter { (_, result) -> result is TwoRoots }
    .also { println("Total with two roots: ${it.size}")}
    .forEach { (eq, result) ->
        result as TwoRoots
        println("$eq -> x1 = ${String.format("%.2f", result.x1)}, x2 = ${String.format("%.2f", result.x2)}")
    }

