data class OrderItem(
    val name: String,
    val price: Double,
    val quantity: Int
)

class Order(val id: String) {
    var customerName: String = ""
    var deliveryAddress: String = ""
    var discountPercent: Int = 0
    val items: MutableList<OrderItem> = mutableListOf()

    fun addItem(item: OrderItem) {
        items.add(item)
    }
}

val order = Order(id = "ORD-2026-001")
    .apply {
        customerName = "Олексій Коваленко"
        deliveryAddress = "вул. Хрещатик, 22, Київ"
        discountPercent = 10
        addItem(OrderItem("Навушники", 4500.0, 2))
        addItem(OrderItem("Крісло", 12000.0, 1))
        addItem(OrderItem("Лампа", 1200.0, 2))
    }
    .also {
        println("[LOG] Замовлення ${it.id} налаштовано. Кількість позицій:z ${it.items.size}")
    }

val finalPrice = order
    .run {
        var total = 0.0
        for (item in items) {
            total += item.price * item.quantity
        }
        total *= (1 - discountPercent * 0.01)
        println("[LOG] Замовлення $id пораховано. Сума замовлення: $total")
        total
    }

val paymentPayload = finalPrice
    .let {
        val sum = (it * 100).toLong()
        "TXN-${order.id}_AMOUNT_${it}_UAH"    
    }
    .also {
        println(it)
    }

println("")

with(order) {
    println("""========================================
ЧЕК ЗАМОВЛЕННЯ: $id
Отримувач: $customerName
Адреса доставки: $deliveryAddress
----------------------------------------""")
    println("Товари:")
    for (item in items) {
        with(item) {
            println("• $name ($quantity шт.) - ${quantity * price} грн")
        }
    }
    println(
                            """----------------------------------------
Знижка клієнта: ${discountPercent}%
Разом до сплати: $finalPrice грн
========================================""")
}
   
