data class Vehicle(
    var brand: String = "",
    var model: String = "",
    var year: Int = 0,
    var licensePlate: String = ""
)

fun main() {
    val toyota = Vehicle()
        .apply {
            brand = "Toyota"
            model = "Hilux"
            year = 1999
            licensePlate = "ПУСЯ"
        }
        .also {
            println("Створено новий транспортний засіб: $it")
        }

    with(toyota) {
        print("Марка = $brand\nМодель = $model\nРік випуску: $year\nНомерний знак: $licensePlate\n")
    }
}

main()

