import kotlin.random.Random

fun generateRandomArray(size: Int, maxValue: Int): IntArray? {
    if (size <= 0 || maxValue <= 0) return null
    return IntArray(size) { Random.nextInt(0, maxValue + 1) }
}

fun main() {
    generateRandomArray(size = 10, maxValue = 50)
        ?.let { array ->
            for (i in array.indices) {
                array[i] = if (array[i] % 2 == 0) {
                        array[i] / 2 }
                                                  else {
                        array[i] * 2                                            
                    } 
                } 
            array
        }
        .also {
            println("${it.contentToString()}")
        }
        ?.run {
            maxOrNull()
        }
        .also {
            println("$it")
        }
    ?: println("Помилка вхідних даних")
}

main()
