package com.example.hw2_16

import android.app.Application
import androidx.lifecycle.ViewModel
import androidx.work.ExistingPeriodicWorkPolicy
import androidx.work.PeriodicWorkRequestBuilder
import androidx.work.WorkManager
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import java.util.concurrent.TimeUnit

class WaterReminderViewModel(private val application: Application) : ViewModel() {

    val _isScheduled = MutableStateFlow(false)
    val isScheduled: StateFlow<Boolean> = _isScheduled.asStateFlow()

    fun startReminder(intervalMinutes: Long) {
        // Враховуємо системне обмеження в 15 хвилин
        val safeInterval = if (intervalMinutes < 15) 15L else intervalMinutes

        val request = PeriodicWorkRequestBuilder<WaterReminderWorker>(
            safeInterval, TimeUnit.MINUTES
        ).build()

        WorkManager.getInstance(application).enqueueUniquePeriodicWork(
            "water_reminder",
            ExistingPeriodicWorkPolicy.UPDATE,
            request
        )
        _isScheduled.update { true }
    }

    fun stopReminder() {
        WorkManager.getInstance(application).cancelUniqueWork("water_reminder")
        _isScheduled.update { false }
    }
}