fun repeatN(n: Int, action: () -> Unit) {
    for (i in 1..n) {
        action()
    }
}

repeatN(5, { println("Hello") })

