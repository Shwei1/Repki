package com.example.hw2_17

import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Query
import java.time.LocalDate
import java.time.format.DateTimeFormatter

interface PrivatBankApi {
    // GET https://api.privatbank.ua/p24api/exchange_rates?json&date="$date"
    @GET("exchange_rates?json")
    fun getExchangeRates(
        @Query("date") date: String = LocalDate
            .now()
            .format(
            DateTimeFormatter
                .ofPattern("dd.MM.yyyy"))
    ): Call<ExchangeArchiveResponse?>?
}