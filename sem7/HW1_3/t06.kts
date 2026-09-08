fun filterStrings(lst: List<String>, phi: (String) -> Boolean): List<String> {
    var res: MutableList<String> = mutableListOf()
    for (str in lst) {
        if (phi(str)) {
            res.add(str)
        }
    }
    return res
}

val strs = listOf("pi0", "bibi", "p03")
val predicate = { str: String -> str.any({ it.isDigit() }) }
println(filterStrings(strs, predicate))
