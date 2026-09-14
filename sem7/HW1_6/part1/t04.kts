data class User(val username: String, val isActive: Boolean)

fun getActiveUsernames(users: List<User>): List<String> {
    return users.mapNotNull { user -> user.username.takeIf { user.isActive } }
}

val allUsers = listOf(
    User("alice123", true),
    User("bob_the_builder", false),
    User("charlie99", true)
)

println(getActiveUsernames(allUsers))

