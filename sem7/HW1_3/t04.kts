val lst = List(100) { (-100..100).random() }

val newLst = lst
    .filter({ x -> x > 0})
    .filter({ x -> x % 5 == 0 })
    .map({ x -> x * x })
    .sortedDescending()
    .also({ nums -> println(nums.max()); println(nums.min())})
    .map({ x -> x.toString() })
    .joinToString(" ")

println(newLst)

