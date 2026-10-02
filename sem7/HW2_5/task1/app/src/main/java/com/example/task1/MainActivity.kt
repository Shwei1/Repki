package com.example.task1

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import com.example.task1.ui.theme.Task1Theme

class MainActivity : ComponentActivity() {
    private val audioPlayer = AudioPlayer()

    private val analyticsTracker = AnalyticsTracker()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            val context = LocalContext.current

            Column(modifier = Modifier.fillMaxSize()) {
                Text("Main Activity")
                Button(onClick = {
                    context.startActivity(Intent(context, SecondActivity::class.java))
                }) {
                    Text("Open second screen")
                }
            }
        }
        lifecycle.addObserver(audioPlayer)
        lifecycle.addObserver(analyticsTracker)
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    Task1Theme {
        Greeting("Android")
    }
}