package com.example.hw2_10

import kotlinx.coroutines.delay
import timber.log.Timber
import kotlin.time.Duration.Companion.milliseconds

class SearchRepository {

    val repoData = listOf("Kyiv", "Kropyvnytskyi", "Kharkiv", "Ukraine", "Moldova")

    suspend fun search(query: String): List<String> {
        Timber.d("Search: query=$query")
        delay(500.milliseconds)
        return repoData.filter { it.contains(query, ignoreCase=true) }
    }
}