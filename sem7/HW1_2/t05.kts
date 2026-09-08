for (i in 1..100) {
    if (i % 3 == 0 && i % 5 == 0) {
        println("$i is fizzbuzz")
    } else if (i % 3 == 0) {
        println("$i is fizz")
    } else if (i % 5 == 0) {
        println("$i is buzz")
    } else {
        println("$i")
    }
}
