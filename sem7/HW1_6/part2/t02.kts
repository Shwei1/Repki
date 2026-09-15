import kotlin.random.Random

fun generateRandomArray(size: Int, maxValue: Int): IntArray? {
    if (size <= 0 || maxValue <= 0) return null
    return IntArray(size) { Random.nextInt(0, maxValue + 1) }
}

generateRandomArray(size = 10, maxValue = 50)
    ?.apply {
        for (i in indices) {
            if (this[i] % 2 == 0) this[i] / 2 else this[i] * 2
        }
    }
    .also {
        println("${it.contentToString()}")
    }
    ?.run {
        maxOrNull()
    }
    .also {
        "$it"
    }
?: "Помилка вхідних даних\n"

