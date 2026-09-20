import kotlin.random.Random

data class ArraySummary(
    val maxElement: Int,
    val elementsOverLimit: Int,
    val totalSum: Int
)

fun generateRandomArray(size: Int, maxValue: Int): IntArray {
    require(size > 0 && maxValue > 0) { "Розмір та максимальне значення мають бути більшими за нуль" }
    return IntArray(size) { kotlin.random.Random.nextInt(1, maxValue + 1) }
}

fun main() {
    generateRandomArray(size = 8, maxValue = 40)
        .also {
            println("Початковий масив: ${it.contentToString()}")
        }
        .apply {
            for (i in indices) {
                this[i] = if (this[i] % 2 == 0) this[i] / 2 else this[i] * 2
            }
        }
        .also {
            println("Модифікований масив: ${it.contentToString()}")
        }
        .run {
            ArraySummary(
                maxElement = reduce { max, x -> maxOf(max, x) },
                elementsOverLimit = count { it > 20 },
                totalSum = fold(0) { acc, n -> acc + n }
            )
        }
        .let {
                                  """
----------------------------------------
ЗВІТ ОБРОБКИ МАСИВУ:
• Найбільше значення: ${it.maxElement}
• Кількість елементів > 20: ${it.elementsOverLimit}
• Сумарне значення: ${it.totalSum}
----------------------------------------
                                  """
        }
        .also {
            println("$it")
        }
}

main()
