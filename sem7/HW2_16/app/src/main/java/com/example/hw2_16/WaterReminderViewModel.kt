package com.example.hw2_16

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.work.ExistingPeriodicWorkPolicy
import androidx.work.PeriodicWorkRequestBuilder
import androidx.work.WorkManager
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import java.util.concurrent.TimeUnit

class WaterReminderViewModel(application: Application): AndroidViewModel(application) {

    val _isScheduled = MutableStateFlow(false)
    val isScheduled: StateFlow<Boolean> = _isScheduled.asStateFlow()

    private val settings = ValuesRepository(application.dataStore)

    val notificationsSent: StateFlow<Int> = settings.notificationAmount
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5_000), 0)

    fun startReminder(intervalMinutes: Long) {
        // Враховуємо системне обмеження в 15 хвилин
        val safeInterval = if (intervalMinutes < 15) 15L else intervalMinutes

        val request = PeriodicWorkRequestBuilder<WaterReminderWorker>(
            safeInterval, TimeUnit.MINUTES
        )
            .setInitialDelay(safeInterval, TimeUnit.MINUTES)
            .build()

        WorkManager.getInstance(getApplication()).enqueueUniquePeriodicWork(
            "water_reminder",
            ExistingPeriodicWorkPolicy.UPDATE,
            request
        )
        _isScheduled.update { true }
    }

    fun stopReminder() {
        WorkManager.getInstance(getApplication()).cancelUniqueWork("water_reminder")
        _isScheduled.update { false }
    }
}