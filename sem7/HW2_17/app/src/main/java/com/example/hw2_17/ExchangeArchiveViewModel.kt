package com.example.hw2_17

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import java.time.LocalDate
import java.time.format.DateTimeFormatter
import java.time.format.DateTimeParseException

class ExchangeArchiveViewModel(application: Application) : AndroidViewModel(application) {

    private val currentDate = LocalDate.now()
        .format(DateTimeFormatter.ofPattern("dd.MM.yyyy"))

    private val networkModule = PrivatBankNetworkModule()

    private val _pickedDate = MutableStateFlow(currentDate)
    val pickedDate = _pickedDate.asStateFlow()

    private val _uiState = MutableStateFlow<ExchangeRatesUiState>(ExchangeRatesUiState.Loading)
    val uiState = _uiState.asStateFlow()

    private var currentCall: Call<ExchangeArchiveResponse?>? = null

    init {
        fetchArchive()
    }

    fun fetchArchive() {
        currentCall?.cancel()
        _uiState.value = ExchangeRatesUiState.Loading

        val call = networkModule.service.getExchangeRates(_pickedDate.value)

        if (call == null) {
            _uiState.value = ExchangeRatesUiState.Error("Не вдалося створити запит")
            return
        }

        currentCall = call
        call.enqueue(object : Callback<ExchangeArchiveResponse?> {
            override fun onResponse(
                call: Call<ExchangeArchiveResponse?>,
                response: Response<ExchangeArchiveResponse?>
            ) {
                if (call !== currentCall || call.isCanceled) return

                val archive = response.body()

                _uiState.value = when {
                    !response.isSuccessful -> ExchangeRatesUiState.Error(
                        "Сервер повернув HTTP ${response.code()}. Спробуйте пізніше."
                    )
                    archive == null -> ExchangeRatesUiState.Error(
                        "Сервер повернул відповідь без даних."
                    )
                    else -> ExchangeRatesUiState.Success(archive)
                }
            }

            override fun onFailure(call: Call<ExchangeArchiveResponse?>, t: Throwable) {
                if (call !== currentCall || call.isCanceled) return

                _uiState.value = ExchangeRatesUiState.Error(
                    "Не вдалося отримати курси. Спробуйте ще раз."
                )
            }
        })
    }

    override fun onCleared() {
        currentCall?.cancel()
        super.onCleared()
    }

    private fun parseDateOrNull(date: String): LocalDate? =
        try {
            LocalDate.parse(date,
                DateTimeFormatter.ofPattern("dd.MM.yyyy"))
        } catch(_: DateTimeParseException) {
            null
        }


    fun onDateChosen(date: String) {
        val parsedDate = parseDateOrNull(date)
        if (parsedDate != null && !parsedDate.isAfter(LocalDate.now())) {
            _pickedDate.value = date
            fetchArchive()
        } // Інакше ігноруємо
    }

}