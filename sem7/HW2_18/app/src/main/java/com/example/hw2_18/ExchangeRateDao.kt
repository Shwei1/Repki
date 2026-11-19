package com.example.hw2_18

import androidx.room3.Dao
import androidx.room3.Query
import androidx.room3.Upsert
import kotlinx.coroutines.flow.Flow

@Dao
interface ExchangeRateDao {

    @Query("SELECT * FROM exchange_rates WHERE date = :date ORDER BY currency ASC")
    fun observeRates(date: String): Flow<List<ExchangeRateEntity>>

    @Query("""
    SELECT DISTINCT date FROM exchange_rates
    ORDER BY substr(date, 7, 4) DESC, substr(date, 4, 2) DESC, substr(date, 1, 2) DESC
""")
    fun observeSavedDates(): Flow<List<String>>

    @Upsert
    suspend fun upsertRates(rates: List<ExchangeRateEntity>)

}