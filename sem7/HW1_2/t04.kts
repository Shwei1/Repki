var pizzaSlices = 1

while (pizzaSlices < 8) {
    println("There's only $pizzaSlices slice/s of pizza :(")
    ++pizzaSlices
}

println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza! :D")

pizzaSlices = 1

do {
    println("There's only $pizzaSlices slice/s of pizza :(")
    ++pizzaSlices
} while (pizzaSlices < 8)

println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza! :D")
