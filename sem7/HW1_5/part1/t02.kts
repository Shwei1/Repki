data class User(val id: Int, var email: String)

fun updateEmail(user: User, newEmail: String): User = user
    .apply { email = newEmail }
    .also { println("Updating email for user with ID: ${it.id}") }

val user = User(1, "old_email@example.com")
val updatedUser = updateEmail(user, "new_email@example.com")
println("Updated User: $updatedUser")
