package com.example.hw2_18

import androidx.room3.Entity

@Entity(tableName = "exchange_rates", primaryKeys = ["date", "currency"])
data class ExchangeRateEntity(
    val date: String,
    val baseCurrency: String,
    val currency: String,
    val purchaseRate: Double?,
    val saleRate: Double?,
)
