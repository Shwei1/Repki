package com.example.hw2_18

data class ExchangeRatesUiState(
    val rates: List<ExchangeRateEntity>,
    val syncStatus: SyncStatus
)