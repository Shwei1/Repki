data class Address(
    val street: String,
    val city: String?,
    val postalCode: String?
)

data class Client(
    val id: Int,
    val name: String,
    val email: String?,
    val address: Address?,
    val extraData: Any? // Може містити рядок, число або null
)

val clientList = listOf(
    Client(
        id = 1,
        name = "Олена",
        email = "olena@example.com",
        address = Address("вул. Саксаганського, 10", "Київ", "01033"),
        extraData = "VIP-клієнт"
    ),
    Client(
        id = 2,
        name = "Богдан",
        email = null,
        address = Address("вул. Городоцька, 45", "Львів", null),
        extraData = 42
    ),
    Client(
        id = 3,
        name = "Марія",
        email = "maria@example.com",
        address = null,
        extraData = null
    ),
    Client(
        id = 4,
        name = "Дмитро",
        email = null,
        address = Address("вул. Соборна, 1", null, null),
        extraData = "Очікує дзвінка"
    )
)

println("\n--- Завдання 1 ---")

fun getShippingLabel(client: Client): String {
    val validAddress =
        client.address
        ?: return "Самовивіз: Клієнт ${client.name} не надав адреси"
    
    val validCity = client.address?.city ?: "Місто не вказано"
    
    val validCode = client.address?.postalCode ?: "Індекс невідомий"

    return "${validAddress.street}, $validCity, $validCode"

    
}
clientList
    .filter { it.name != "Дмитро"}
    .forEach { println("Адреса ${it.name}: ${getShippingLabel(it)}") }


println("\n--- Завдання 2 ---")

fun printClientNote(client: Client) {
    val validNote = client.extraData as? String ?: "Додаткові примітки відсутні"
    println("Клієнт ${client.name} -> Примітка: $validNote")
}

clientList.forEach { printClientNote(it) }


println("\n--- Завдання 3 ---")

val res = clientList
    .map { it.email }
    .filterNotNull()
    .also { println("$it") }
    .minByOrNull { it.length }
    .also { println("${it?.length}")}

println("\n--- Завдання 4 ---")

fun getClientEmailOrThrow(client: Client): String = requireNotNull(client.email) { "Клієнт з ID ${client.id} не має електронної пошти!" }

try {
    clientList
        .find { it.id == 2 }
        ?.also { getClientEmailOrThrow(it) }
} catch (e: IllegalArgumentException) {
    println("${e.message}")
}

println("\n--- Завдання 5 ---")

fun forceGetPostalCode(client: Client): String = client.address?.postalCode!!

clientList
    .find { it.id == 1 }
    ?.also { println("Перехоплено виняток: ${forceGetPostalCode(it)}") }

var res2 = try {
clientList
    .find { it.id == 2 }
    ?.also { println("${forceGetPostalCode(it)}") }
} catch (e: NullPointerException) {
    println("Перехоплено виняток: ${e.message}")
}

// Оператор !! слід застосовувати, коли умови подальшого виконання серйозно порушені і помилка має припиняти виконання програми негайно.
// Наприклад, якщо подальше виконання програми може пошкодити стан якихось даних чи становити будь-яку іншу загорзу

