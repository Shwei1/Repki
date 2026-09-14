data class ProductInfo(val priceInDollars: Double?)

class Product {
    fun getProductInfo(): ProductInfo? {
        return ProductInfo(100.0)
    }
}

fun Product.getPriceInEuros() = getProductInfo()
    ?.priceInDollars
    ?.let { convertToEuros(it) }

fun convertToEuros(dollars: Double): Double {
    return dollars * 0.85
}

val product = Product()
val priceInEuros = product.getPriceInEuros()

if (priceInEuros != null) {
    println("Price in Euros: €$priceInEuros")
} else {
    println("Price information is not available.")
}
