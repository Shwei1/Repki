fun validateStock(requested: Int?, available: Int?): Int {
    val wasRequested = requested ?: return -1
    val isAvailable = requested ?: return -1

    if (wasRequested < 0) return -1
    if (wasRequested > isAvailable) return -1

    return isAvailable
}


println(validateStock(5,10))
println(validateStock(null,10))
println(validateStock(-2,10))

