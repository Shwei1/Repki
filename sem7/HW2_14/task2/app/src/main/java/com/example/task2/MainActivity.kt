package com.example.task2

import android.Manifest
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.content.ServiceConnection
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.IBinder
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.lifecycleScope
import com.example.task2.ui.theme.Task2Theme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {

    private var isBound = false

    private val _timerFlow = MutableStateFlow<Int>(0)
    private var timerFlow: StateFlow<Int> = _timerFlow.asStateFlow()

    private var timerService: TimerForegroundService? = null
    private val connection = object : ServiceConnection {
        override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
            val binder = service as TimerForegroundService.LocalBinder
            val myService = binder.getService()
            timerService = myService
            isBound = true

            lifecycleScope.launch {
                myService.getTimerFlow().collect { seconds ->
                    _timerFlow.update{ seconds }
                }
            }
        }

        override fun onServiceDisconnected(arg0: ComponentName) {
            timerService = null
            isBound = false
        }




    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        setContent {
            RequestNotificationPermission()
            Task2Theme {
                Row(
                    modifier = Modifier
                        .fillMaxSize()
                        .padding(16.dp)
                ) {
                    ButtonTimerStart()
                    Spacer(Modifier.height(16.dp))
                    ButtonTimerStop()
                }
                Box(
                    modifier = Modifier.fillMaxSize(),
                    contentAlignment = Alignment.Center
                ) {
                    val secs by timerFlow.collectAsStateWithLifecycle()
                    TimerDisplay(secs)
                }
            }
        }

        bindService(
            Intent(this, TimerForegroundService::class.java),
            connection,
            Context.BIND_AUTO_CREATE
        )
    }


    override fun onStop() {
        super.onStop()
        if (isBound) {
            unbindService(connection)
            isBound = false
            timerService = null
        }
    }

    @Composable
    fun RequestNotificationPermission() {
        val context = LocalContext.current;
        val launcher =
            rememberLauncherForActivityResult(ActivityResultContracts.RequestPermission()) {}

        LaunchedEffect(Unit) {
            val alreadyGiven = ContextCompat.checkSelfPermission(
                context, Manifest.permission.POST_NOTIFICATIONS
            ) == PackageManager.PERMISSION_GRANTED
            if (!alreadyGiven) {
                launcher.launch(Manifest.permission.POST_NOTIFICATIONS)
            }
        }

    }

    @Composable
    fun TimerDisplay(seconds: Int) {
        Text(text = "$seconds секунд")
    }

    @Composable
    fun ButtonTimerStart() {
        val context = LocalContext.current;
        Button(
            onClick = {
                val intent = Intent(context, TimerForegroundService::class.java)
                ContextCompat.startForegroundService(context, intent)
            }
        )
        {
            Text("Старт Таймер")
        }
    }

    @Composable
    fun ButtonTimerStop() {
        val context = LocalContext.current;
        Button(
            onClick = { timerService?.stopTimer() }) {
            Text("Стоп Таймер")
        }
    }
}
