package com.example.hw2_18

import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Query

interface PrivatBankApi {
    // GET https://api.privatbank.ua/p24api/exchange_rates?json&date="$date"
    @GET("exchange_rates?json")
    suspend fun getExchangeRates(
        @Query("date") date: String
    ): Response<ExchangeArchiveResponse>
}
