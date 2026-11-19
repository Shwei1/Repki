package com.example.hw2_18

import com.google.gson.annotations.SerializedName

data class ExchangeArchiveResponse(
    val bank: String,
    val baseCurrency: Int,
    val baseCurrencyLit: String,
    val date: String,
    @SerializedName("exchangeRate")
    val exchangeRates: List<ExchangeRate>?
)

// Елементи без коду валюти пропускаються
fun ExchangeArchiveResponse.toEntities(): List<ExchangeRateEntity> =
    exchangeRates.orEmpty()
        .mapNotNull { rate ->
            val currency = rate.currency?.takeIf { it.isNotBlank() }
                ?: return@mapNotNull null
            ExchangeRateEntity(
                date = date,
                baseCurrency = rate.baseCurrency ?: baseCurrencyLit,
                currency = currency,
                purchaseRate = rate.purchaseRate,
                saleRate = rate.saleRate,
            )
        }
