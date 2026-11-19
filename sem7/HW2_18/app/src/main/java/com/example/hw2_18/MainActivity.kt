package com.example.hw2_18

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
import androidx.compose.material3.DatePicker
import androidx.compose.material3.DatePickerDialog
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.OutlinedButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.SelectableDates
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.material3.rememberDatePickerState
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.hw2_18.ui.theme.ComposeTheme
import java.time.LocalDate
import java.time.ZoneOffset
import java.time.Instant

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ComposeTheme {
                val viewModel: ExchangeArchiveViewModel = viewModel()
                val pickedDate by viewModel.pickedDate.collectAsStateWithLifecycle()
                val uiState by viewModel.uiState.collectAsStateWithLifecycle()
                val savedDates by viewModel.savedDates.collectAsStateWithLifecycle()
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    CurrencyRatesScreen(
                        pickedDate = pickedDate,
                        uiState = uiState,
                        savedDates = savedDates,
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
        savedDates: List<String>,
        onDateChosen: (String) -> Unit,
        onLoadRates: () -> Unit,
        modifier: Modifier = Modifier
    ) {

        var showPicker by rememberSaveable { mutableStateOf(false) }
        val syncing = uiState.syncStatus is SyncStatus.Waiting ||
                uiState.syncStatus is SyncStatus.Running

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
                    TextButton(onClick = { showPicker = true }) { Text("Обрати") }
                },
                modifier = Modifier.fillMaxWidth()
            )
            SavedDatesButton(
                savedDates = savedDates,
                pickedDate = pickedDate,
                onDateChosen = onDateChosen
            )
            Button(
                onClick = onLoadRates,
                modifier = Modifier.fillMaxWidth(),
                enabled = !syncing
            ) {
                Text("Оновити")
            }

            when (val s = uiState.syncStatus) {
                SyncStatus.Idle -> {}
                SyncStatus.Waiting -> Text("Очікує мережі / запуску")
                SyncStatus.Running -> Text("Оновлюється")
                is SyncStatus.Done -> Text(s.message ?: "Оновлено")
                is SyncStatus.Failed -> Column {
                    Text(s.message, color = MaterialTheme.colorScheme.error)
                    if (uiState.rates.isNotEmpty()) {
                        Text("Показано раніше збережені курси")
                    }
                }
            }

            RatesList(
                rates = uiState.rates,
                date = pickedDate,
                baseCurrency = "UAH",
                modifier = Modifier.weight(1f)
            )
        }

        if (showPicker) {
            ArchiveDateDialog(
                date = pickedDate,
                onDateChosen = onDateChosen,
                onDismiss = { showPicker = false }
            )
        }
    }

    @Composable
    fun SavedDatesButton(
        savedDates: List<String>,
        pickedDate: String,
        onDateChosen: (String) -> Unit
    ) {
        var expanded by rememberSaveable { mutableStateOf(false) }

        Box {
            OutlinedButton(
                onClick = { expanded = true },
                enabled = savedDates.isNotEmpty(),
                modifier = Modifier.fillMaxWidth()
            ) {
                Text("Збережені дати (${savedDates.size})")
            }
            DropdownMenu(
                expanded = expanded,
                onDismissRequest = { expanded = false }
            ) {
                savedDates.forEach { date ->
                    DropdownMenuItem(
                        text = {
                            Text(
                                date,
                                fontWeight = if (date == pickedDate) FontWeight.Bold else null
                            )
                        },
                        onClick = {
                            onDateChosen(date)
                            expanded = false
                        }
                    )
                }
            }
        }
    }

    @Composable
    fun RatesList(
        rates: List<ExchangeRateEntity>,
        date: String,
        baseCurrency: String,
        modifier: Modifier = Modifier
    ) {
        if (rates.isEmpty()) {
            Box(modifier.fillMaxWidth()) {
                Text(
                    "Курси за цю дату ще не завантажені",
                    Modifier.align(Alignment.Center)
                )
            }
        } else {
            Column(modifier = modifier.fillMaxWidth()) {
                Text(
                    "Курси станом на $date",
                )
                Row(Modifier.fillMaxWidth().padding(vertical = 8.dp)) {
                    Text("Валюта", Modifier.weight(1f))
                    Text("Банк купує ($baseCurrency)", Modifier.weight(1f))
                    Text("Банк продає ($baseCurrency)", Modifier.weight(1f))
                }
                LazyColumn(Modifier.weight(1f)) {
                    items(rates, key = { it.currency }) { rate ->
                        Row(Modifier.fillMaxWidth().padding(vertical = 8.dp)) {
                            val purchaseRateNonNull = rate.purchaseRate?.toString() ?: "—"
                            val saleRateNonNull = rate.saleRate?.toString() ?: "—"
                            Text(rate.currency, Modifier.weight(1f))
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

    @Composable
    fun ArchiveDateDialog(
        date: String,
        onDateChosen: (String) -> Unit,
        onDismiss: () -> Unit
    ) {
        val today = LocalDate.now()
        val minDate = today.minusYears(4)
        val minMillis = minDate.atStartOfDay(ZoneOffset.UTC).toInstant().toEpochMilli()
        val state = rememberDatePickerState(
            initialSelectedDateMillis = LocalDate.parse(date, PrivatApiDateFormatter)
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
            onDismissRequest = { onDismiss() },
            confirmButton = {
                TextButton(
                    onClick = {
                        state.selectedDateMillis?.let { ms ->
                            val date = Instant.ofEpochMilli(ms)
                                .atZone(ZoneOffset.UTC)
                                .toLocalDate()
                            onDateChosen(date.format(PrivatApiDateFormatter))
                            onDismiss()
                        }
                    }
                ) { Text("Ввести") }
            },
            dismissButton = {
                TextButton(onClick = {
                    onDismiss()
                }) { Text("Скасувати") }
            }
        ) { DatePicker(state = state) }
    }
}