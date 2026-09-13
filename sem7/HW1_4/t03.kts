data class Product(
    val id: Int,
    val name: String,
    val category: String,
    val price: Double,
    val rating: Double,
    val inStock: Boolean
)

val products = listOf(
    Product(1, "Google Pixel 9", "Smartphones", 899.0, 4.8, true),
    Product(2, "iPhone 16 Pro", "Smartphones", 1199.0, 4.9, true),
    Product(3, "Galaxy A55", "Smartphones", 399.0, 4.3, false),
    Product(4, "MacBook Air M3", "Laptops", 1299.0, 4.9, true),
    Product(5, "ThinkPad X1 Carbon", "Laptops", 1499.0, 4.6, false),
    Product(6, "Dell XPS 13", "Laptops", 1150.0, 4.4, true),
    Product(7, "Sony WH-1000XM5", "Audio", 349.0, 4.7, true),
    Product(8, "AirPods Pro 2", "Audio", 249.0, 4.8, false),
    Product(9, "Pixel Buds Pro 2", "Audio", 229.0, 4.5, true)
)

println("== Відфільтровані товари ==")
products
    .filter { it -> it.inStock }
    .sortedByDescending { it.rating }
    .map {
        it -> "Назва: ${it.name} | Рейтинг: ${it.rating} | Ціна: ${it.price}"
    }
    .forEach { println(it) }

println("== Пошук ноутбука ==")
products.find { it.category == "Laptops" && it.price > 1200 }
    ?.let { println("${it.name}") }
    ?:let { println("Товар не знайдено") }

println("== Пошук навушників ==")
println("${products.any { it.category == "Audio" && it.price > 300 }}")

println("== Рейтинги телефонів ==")
val result: Boolean = products
    .filter { it.category == "Smartphones" }
    .all { it.price > 300 }
println("$result")


println("== В наявності та не в наявності ==")

val (available, outOfStock) = products.partition { it.inStock }
println("In stock: ${available.count()}")
println("Out of stock: ${outOfStock.count()}")

println("== Розподіл за категоріями ==")
products.groupBy { it.category}
    .forEach {
        (category, prods) ->
        val m = prods.maxByOrNull { it.price }!!
        println("Категорія $category -> Найдорожчий: ${m.name} (\$${m.price})")
    }

println("== Higher Order Function ==")

fun List<Product>.filterAndTransform(
    predicate: (Product) -> Boolean,
    transform: (Product) -> String
): List<String> {
    val res: MutableList<String> = mutableListOf()
    for (el in this) {
        if (predicate(el)) {
            res.add(transform(el))
        }
    }
    return res
}


products
    .filterAndTransform({it.price < 300})
                       { "Акційна ціна на ${it.name}: лише \$${it.price}"}
    .forEach { println(it) }

println("== Додатково ==")

val res = products
    .filter { it.inStock }
    .fold(0.0 to 0) { acc, product -> (acc.first + product.price) to (acc.second + 1) }
    .also { println("Сума: ${it.first}, Середнє: ${it.first/it.second}") }

