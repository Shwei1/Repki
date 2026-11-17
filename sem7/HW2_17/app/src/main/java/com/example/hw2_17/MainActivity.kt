package com.example.hw2_17

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.DatePicker
import androidx.compose.material3.DatePickerDialog
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.SelectableDates
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.material3.rememberDatePickerState
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.hw2_17.ui.theme.ComposeTheme
import java.time.LocalDate
import java.time.ZoneOffset
import java.time.format.DateTimeFormatter
import java.time.Instant

class MainActivity : ComponentActivity() {

    private val formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ComposeTheme {
                val viewModel: ExchangeArchiveViewModel = viewModel()
                val pickedDate by viewModel.pickedDate.collectAsStateWithLifecycle()
                val uiState by viewModel.uiState.collectAsStateWithLifecycle()
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    CurrencyRatesScreen(
                        pickedDate = pickedDate,
                        uiState = uiState,
                        onDateChosen = viewModel::onDateChosen,
                        onLoadRates = viewModel::fetchArchive,
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }


    @Composable
    fun CurrencyRatesScreen(
        pickedDate: String,
        uiState: ExchangeRatesUiState,
        onDateChosen: (String) -> Unit,
        onLoadRates: () -> Unit,
        modifier: Modifier = Modifier
    ) {

        var showPicker by rememberSaveable { mutableStateOf(false) }

        Column(
            modifier = modifier
                .fillMaxSize()
                .padding(16.dp),
            verticalArrangement = Arrangement.spacedBy(16.dp)
        ) {
            OutlinedTextField(
                value = pickedDate,
                onValueChange = {},
                readOnly = true,
                label = { Text("Дата") },
                trailingIcon = {
                    TextButton(onClick = { showPicker = true }, enabled = uiState !is ExchangeRatesUiState.Loading) { Text("Обрати") }
                },
                modifier = Modifier.fillMaxWidth()
            )
            Button(
                onClick = onLoadRates,
                modifier = Modifier.fillMaxWidth(),
                enabled = uiState !is ExchangeRatesUiState.Loading
            ) {
                Text("Показати курси")
            }

            Box(Modifier.fillMaxWidth().weight(1f)) {
                when (uiState) {
                    ExchangeRatesUiState.Start ->
                        Column(Modifier.align(Alignment.Center)) {
                            Text("Введіть дату, щоб подивитися курс валют.")
                        }
                    ExchangeRatesUiState.Loading ->
                        CircularProgressIndicator(Modifier.align(Alignment.Center))

                    is ExchangeRatesUiState.Error -> Column(
                        Modifier.align(Alignment.Center),
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        Text(uiState.message)
                        Button(onClick = onLoadRates) { Text("Повторити") }
                    }

                    is ExchangeRatesUiState.Success -> {
                        val rates = uiState.archive.exchangeRate
                            .filter { !it.currency.isNullOrBlank()}
                        if (rates.isEmpty()) {
                            Text(
                                "Немає даних за ${uiState.archive.date}",
                                Modifier.align(Alignment.Center)
                            )
                        } else {
                            Column(modifier = Modifier.fillMaxSize()) {
                                Text(
                                    "Курси станом на ${uiState.archive.date}",
                                )
                                Row(Modifier.fillMaxWidth().padding(vertical = 8.dp)) {
                                    Text("Валюта", Modifier.weight(1f))
                                    Text("Банк купує (${uiState.archive.baseCurrencyLit})", Modifier.weight(1f))
                                    Text("Банк продає (${uiState.archive.baseCurrencyLit})", Modifier.weight(1f))
                                }
                                LazyColumn(Modifier.weight(1f)) {
                                    items(rates, key = { it.currency!! }) { rate ->
                                        Row(Modifier.fillMaxWidth().padding(vertical = 8.dp)) {
                                            val purchaseRateNonNull = rate.purchaseRate?.toString() ?: "-"
                                            val saleRateNonNull = rate.saleRate?.toString() ?: "-"
                                            Text(rate.currency!!, Modifier.weight(1f))
                                            Text(
                                                purchaseRateNonNull,
                                                Modifier.weight(1f)
                                            )
                                            Text(
                                                saleRateNonNull,
                                                Modifier.weight(1f)
                                            )
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (showPicker) {
            val today = LocalDate.now()
            val minDate = today.minusYears(ExchangeArchiveViewModel.ARCHIVE_YEARS)
            val minMillis = minDate.atStartOfDay(ZoneOffset.UTC).toInstant().toEpochMilli()
            val state = rememberDatePickerState(
                initialSelectedDateMillis = LocalDate.parse(pickedDate, formatter)
                    .atStartOfDay(ZoneOffset.UTC)
                    .toInstant()
                    .toEpochMilli(),
                yearRange = minDate.year..today.year,
                selectableDates = object : SelectableDates {
                    override fun isSelectableDate(utcTimeMillis: Long) =
                        utcTimeMillis in minMillis..System.currentTimeMillis()

                    override fun isSelectableYear(year: Int) =
                        year in minDate.year..today.year
                }
            )
            DatePickerDialog(
                onDismissRequest = { showPicker = false },
                confirmButton = {
                    TextButton(
                        onClick = {
                            state.selectedDateMillis?.let { ms ->
                                val date = Instant.ofEpochMilli(ms)
                                    .atZone(ZoneOffset.UTC)
                                    .toLocalDate()
                                onDateChosen(date.format(formatter))
                                showPicker = false
                            }
                        }
                    ) { Text("Ввести") }
                },
                dismissButton = {
                    TextButton(onClick = {
                        showPicker = false
                    }) { Text("Скасувати") }
                }
            ) { DatePicker(state = state) }
        }
    }
}