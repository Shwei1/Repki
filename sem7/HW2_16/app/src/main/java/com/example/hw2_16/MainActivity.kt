package com.example.hw2_16

import android.Manifest
import android.app.Application
import android.content.Context
import android.content.pm.PackageManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Switch
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableLongStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.Preferences
import androidx.datastore.preferences.preferencesDataStore
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewModelScope
import com.example.hw2_16.ui.theme.HW2_16Theme

val Context.dataStore: DataStore<Preferences> by preferencesDataStore(name = "settings")

class MainActivity : ComponentActivity() {

    val viewModel: WaterReminderViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            RequestNotificationPermission()
            HW2_16Theme {
                WaterReminderScreen(viewModel)
            }
        }
    }
}

@Composable
fun WaterReminderScreen(
    viewModel: WaterReminderViewModel
) {
    val state by viewModel.isScheduled.collectAsStateWithLifecycle()
    val sent by viewModel.notificationsSent.collectAsStateWithLifecycle()
    var intervalText by rememberSaveable { mutableStateOf("60") }

    val interval = intervalText.toLongOrNull()
    val isErr = interval == null || interval < 15


    Column(Modifier.padding(24.dp), verticalArrangement = Arrangement.spacedBy(16.dp)) {
        InputTextBox(
            intervalText,
            { intervalText = it },
            isErr,
            modifier = Modifier.fillMaxWidth()
        )
        ReminderSwtich(
            checked = state,
            enabled = !isErr || state,
            onCheckedChange = { on ->
                if (on) {
                    viewModel.startReminder(interval!!) // safe because model checks
                } else {
                    viewModel.stopReminder()
                }
            },
            modifier = Modifier.padding(top = 8.dp)
        )
        Text("Відправлено $sent оповіщень.")
    }
}

@Composable
fun InputTextBox(
    value: String,
    onValueChange: (String) -> Unit,
    isErr: Boolean,
    modifier: Modifier
) {
    OutlinedTextField(
        value = value,
        onValueChange = { new: String ->
            if (new.all(Char::isDigit) && new.length < 4) {
                onValueChange(new)
            }
        },
        label = { Text("Інтервал (хв)") },
        singleLine = true,
        isError = isErr,
        supportingText = { if (isErr) Text("Інтервал має бути 15 хв або більше!") },
        keyboardOptions = KeyboardOptions(
            keyboardType = KeyboardType.Number,
            imeAction = ImeAction.Done
        ),
        modifier = modifier
    )
}

@Composable
fun ReminderSwtich(
    checked: Boolean,
    enabled: Boolean,
    onCheckedChange: (Boolean) -> Unit,
    modifier: Modifier
) {
    Row(modifier.fillMaxWidth(), verticalAlignment = Alignment.CenterVertically) {
        Text("Нагадування", Modifier.weight(1f))
        Switch(checked = checked, enabled = enabled, onCheckedChange = onCheckedChange)
    }
}

@Composable
fun RequestNotificationPermission() {
    val context = LocalContext.current;
    val launcher = rememberLauncherForActivityResult(ActivityResultContracts.RequestPermission()){}

    LaunchedEffect(Unit) {
        val alreadyGiven = ContextCompat.checkSelfPermission(
            context, Manifest.permission.POST_NOTIFICATIONS
        ) == PackageManager.PERMISSION_GRANTED
        if (!alreadyGiven) {
            launcher.launch(Manifest.permission.POST_NOTIFICATIONS)
        }
    }
}

