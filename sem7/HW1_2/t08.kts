fun intervalInSeconds(hours: Int = 0, minutes: Int = 0, seconds: Int = 0): Int
                                                                           = hours * 3600 + minutes * 60 + seconds

println(intervalInSeconds(hours = 1, minutes = 20, seconds = 15))
println(intervalInSeconds(minutes = 1, seconds = 25))
println(intervalInSeconds(hours = 2))
println(intervalInSeconds(minutes = 10))
println(intervalInSeconds(hours = 1, seconds = 1))
