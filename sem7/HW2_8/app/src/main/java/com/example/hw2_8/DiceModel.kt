package com.example.hw2_8

import kotlinx.coroutines.async
import kotlinx.coroutines.awaitAll
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.delay
import kotlin.random.Random
import kotlin.time.Duration.Companion.milliseconds

class DiceModel {

    suspend fun rollDie(): Int {
        delay(100.milliseconds)
        return Random.nextInt(1, 7);
    }

    suspend fun rollAll(onFace: (index: Int, value: Int) -> Unit) = coroutineScope {
        List(6) { i ->
            async {
                val duration = Random.nextLong(1500, 3000);
                var elapsed = 0L
                while (elapsed < duration) {
                    onFace(i, rollDie())
                    elapsed += 100
                }
            }
        }.awaitAll()
    }
}