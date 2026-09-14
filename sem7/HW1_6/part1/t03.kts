data class Subscription(val name: String, val isActive: Boolean)

// fun getActiveSubscription(subscriptions: List<Subscription>): Subscription? = if (subscriptions.count { it.isActive } > 1) null else subscriptions.find { it.isActive }

fun getActiveSubscription(subscriptions: List<Subscription>): Subscription? = subscriptions.singleOrNull { it.isActive }

 val userWithPremiumPlan = listOf(
     Subscription("Basic Plan", false),
     Subscription("Premium Plan", true)
 )

 val userWithConflictingPlans = listOf(
     Subscription("Basic Plan", true),
     Subscription("Premium Plan", true)
 )

 println(getActiveSubscription(userWithPremiumPlan))

 println(getActiveSubscription(userWithConflictingPlans))
