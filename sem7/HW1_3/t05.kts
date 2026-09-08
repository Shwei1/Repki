fun filterStringsCount(lst: List<String>, phi: (String) -> Boolean): Int {
    var res = 0
    for (str in lst) {
        if (phi(str)) {
            ++res;
        }
    }
    return res
}

val strs = listOf("pi0", "bibi", "p03")
val predicate = { str: String -> str.any({ it.isDigit() }) }
println(filterStringsCount(strs, predicate))
