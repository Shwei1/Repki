package com.example.hw2_17

sealed interface ExchangeRatesUiState {
    data object Start: ExchangeRatesUiState
    data object Loading: ExchangeRatesUiState
    data class Success(val archive: ExchangeArchiveResponse): ExchangeRatesUiState
    data class Error(val message: String): ExchangeRatesUiState
}