package com.example.hw2_18

// DTO відповіді API: Gson може залишити поля null, тому вони nullable.
// Сутність Room (ExchangeRateEntity) лишається non-null.
data class ExchangeRate(
    val baseCurrency: String?,
    val currency: String?,
    val purchaseRate: Double?,
    val purchaseRateNB: Double?,
    val saleRate: Double?,
    val saleRateNB: Double?
)
