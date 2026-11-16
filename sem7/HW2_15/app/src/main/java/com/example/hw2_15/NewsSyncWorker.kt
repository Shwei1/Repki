package com.example.hw2_15

import android.content.Context
import androidx.work.CoroutineWorker
import androidx.work.Data
import androidx.work.WorkerParameters
import kotlinx.coroutines.delay
import kotlin.time.Duration.Companion.milliseconds

class NewsSyncWorker(
    context: Context,
    workerParams: WorkerParameters
) : CoroutineWorker(context, workerParams) {

    override suspend fun doWork(): Result {
        val token = inputData.getString("user_token")
        delay(3000.milliseconds)
        val out = Data.Builder().putString("result", "Успіх!").build()
        return Result.success(out)
    }
}