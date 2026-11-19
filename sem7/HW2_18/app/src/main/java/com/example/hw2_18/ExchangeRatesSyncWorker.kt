package com.example.hw2_18

import android.content.Context
import androidx.work.CoroutineWorker
import androidx.work.WorkerParameters
import androidx.work.workDataOf
import kotlinx.coroutines.CancellationException
import java.io.IOException
import java.time.LocalDate

class ExchangeRatesSyncWorker(
    context: Context,
    params: WorkerParameters
): CoroutineWorker(context, params) {

    private val exchangeRateDao = ExchangeDatabase
        .getDatabase(applicationContext)
        .exchangeRateDao()

    override suspend fun doWork(): Result {
        val date = inputData.getString("date") ?: LocalDate
            .now()
            .format(PrivatApiDateFormatter)

        return try {
            val response = PrivatBankNetworkModule.service.getExchangeRates(date)
            if (!response.isSuccessful) {
                return when (response.code()) {
                    in 500..599, 429 -> Result.retry()
                    else -> failure("Помилка запиту: HTTP ${response.code()}")
                }
            }

            val body = response.body()
                ?: return failure("Сервер повернув порожню відповідь")

            if (body.date != date)
                return failure("Сервер повернув курси за іншу дату (${body.date})")

            val entities = body.toEntities()

            if (entities.isEmpty())
                return failure("Сервер не повернув курсів")

            exchangeRateDao.upsertRates(entities)
            Result.success()
        } catch (_: IOException) {
            Result.retry()
        } catch (e: CancellationException) {
            throw e
        } catch (e: Exception) {
            failure("Unexpected response: ${e.message}")
        }
    }

    private fun failure(message: String) =
        Result.failure(workDataOf("message" to message))
}
