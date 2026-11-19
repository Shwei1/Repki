package com.example.hw2_18

import android.content.Context
import androidx.room3.Database
import androidx.room3.Room
import androidx.room3.RoomDatabase
import androidx.sqlite.driver.AndroidSQLiteDriver

@Database(entities = [ExchangeRateEntity::class], version = 1, exportSchema = false)
abstract class ExchangeDatabase : RoomDatabase() {

    abstract fun exchangeRateDao(): ExchangeRateDao

    companion object {
        @Volatile
        private var INSTANCE: ExchangeDatabase? = null

        fun getDatabase(context: Context): ExchangeDatabase {

            return INSTANCE ?: synchronized(this) {

                INSTANCE?.let { return it }

                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    ExchangeDatabase::class.java,
                    "exchange_rates.db"
                )
                    .setDriver(AndroidSQLiteDriver())
                    .build()

                INSTANCE = instance
                instance
            }
        }

    }

}