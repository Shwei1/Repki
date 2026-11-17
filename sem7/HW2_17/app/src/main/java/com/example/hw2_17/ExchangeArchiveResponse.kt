package com.example.hw2_17

data class ExchangeArchiveResponseX(
    val bank: String,
    val baseCurrency: Int,
    val baseCurrencyLit: String,
    val date: String,
    val exchangeRate: List<ExchangeRate>
)