package com.example.hw2_18

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.viewModelScope
import androidx.work.Constraints
import androidx.work.ExistingWorkPolicy
import androidx.work.NetworkType
import androidx.work.OneTimeWorkRequestBuilder
import androidx.work.WorkInfo
import androidx.work.WorkManager
import androidx.work.workDataOf
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.combine
import kotlinx.coroutines.flow.flatMapLatest
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import java.time.LocalDate
import java.time.format.DateTimeParseException

class ExchangeArchiveViewModel(application: Application) : AndroidViewModel(application) {

    private val currentDate = LocalDate.now()
        .format(PrivatApiDateFormatter)
    private val dao = ExchangeDatabase.getDatabase(application).exchangeRateDao()
    private val workManager = WorkManager.getInstance(application)

    private val _pickedDate = MutableStateFlow(currentDate)
    val pickedDate = _pickedDate.asStateFlow()

    @OptIn(ExperimentalCoroutinesApi::class)
    private val syncState: Flow<SyncStatus> = pickedDate
        .flatMapLatest { date ->
            workManager.getWorkInfosForUniqueWorkFlow("exchange_rates_$date")
                .map { it.firstOrNull() }
        }
        .map { info -> info.toSyncStatus() }
        .stateIn(
            viewModelScope,
            SharingStarted.WhileSubscribed(5_000),
            SyncStatus.Idle)


    @OptIn(ExperimentalCoroutinesApi::class)
    private val rates: StateFlow<List<ExchangeRateEntity>> = pickedDate
        .flatMapLatest { date -> dao.observeRates(date) }
        .stateIn(
            scope = viewModelScope,
            started = SharingStarted.WhileSubscribed(5000),
            initialValue = emptyList()
        )

    val uiState: StateFlow<ExchangeRatesUiState> =
        combine(rates, syncState) {
            rates, status ->
            ExchangeRatesUiState(rates, status)
        }.stateIn(
            scope = viewModelScope,
            started = SharingStarted.WhileSubscribed(5_000),
            initialValue = ExchangeRatesUiState(rates = emptyList(), syncStatus = SyncStatus.Idle)
        )

    val savedDates: StateFlow<List<String>> = dao.observeSavedDates()
        .stateIn(
            scope = viewModelScope,
            started = SharingStarted.WhileSubscribed(5_000),
            initialValue = emptyList()
        )

    fun fetchArchive() {
        val inputData = workDataOf("date" to pickedDate.value)


        val constraints = Constraints
            .Builder()
            .setRequiredNetworkType(NetworkType.CONNECTED)
            .build()

        val request = OneTimeWorkRequestBuilder<ExchangeRatesSyncWorker>()
            .setInputData(inputData)
            .setConstraints(constraints)
            .build()

        workManager.enqueueUniqueWork(
            "exchange_rates_${pickedDate.value}",
            ExistingWorkPolicy.KEEP,
            request
        )
    }

    private fun parseDateOrNull(date: String): LocalDate? =
        try {
            LocalDate.parse(date, PrivatApiDateFormatter)
        } catch(_: DateTimeParseException) {
            null
        }


    fun onDateChosen(date: String) {
        val parsedDate = parseDateOrNull(date)
        val today = LocalDate.now()
        if (parsedDate != null &&
            !parsedDate.isAfter(today) &&
            !parsedDate.isBefore(today.minusYears(ARCHIVE_YEARS))
        ) {
            _pickedDate.value = date
        } // Інакше ігноруємо
    }


    private fun WorkInfo?.toSyncStatus(): SyncStatus = when (this?.state) {
        null -> SyncStatus.Idle
        WorkInfo.State.ENQUEUED, WorkInfo.State.BLOCKED -> SyncStatus.Waiting
        WorkInfo.State.RUNNING -> SyncStatus.Running
        WorkInfo.State.SUCCEEDED -> SyncStatus.Done(
            outputData.getString("message")
        )
        WorkInfo.State.FAILED -> SyncStatus.Failed(
            outputData.getString("message") ?: "Помилка оновлення"
        )
        WorkInfo.State.CANCELLED -> SyncStatus.Failed("Оновлення скасовано")
    }

    val ARCHIVE_YEARS = 4L
}