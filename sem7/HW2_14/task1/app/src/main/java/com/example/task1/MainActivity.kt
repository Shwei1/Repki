package com.example.task1

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
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
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import com.example.task1.ui.theme.Task1Theme

class MainActivity : ComponentActivity() {



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        setContent {
            RequestNotificationPermission()
            Task1Theme {
                Row(
                    modifier = Modifier
                        .fillMaxSize()
                        .padding(16.dp)
                ) {
                    ButtonTimerStart()
                    Spacer(Modifier.height(16.dp))
                    ButtonTimerStop()
                }
            }
        }
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
        onClick = {
            val intent = Intent(context, TimerForegroundService::class.java)
            context.stopService(intent)
        }
    ) {
        Text("Стоп Таймер")
    }
}
