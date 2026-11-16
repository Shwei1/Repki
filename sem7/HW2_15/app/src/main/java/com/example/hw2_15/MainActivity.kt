package com.example.hw2_15

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.work.Constraints
import androidx.compose.ui.unit.dp
import androidx.work.Data
import androidx.work.ExistingPeriodicWorkPolicy
import androidx.work.ExistingWorkPolicy
import androidx.work.NetworkType
import androidx.work.OneTimeWorkRequestBuilder
import androidx.work.PeriodicWorkRequestBuilder
import androidx.work.WorkInfo
import androidx.work.WorkManager
import com.example.hw2_15.ui.theme.HW2_15Theme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import java.util.concurrent.TimeUnit

class MainActivity : ComponentActivity() {

    enum class Status(val string: String) {
        ENQUEUED("Очікує оновлення"),
        UPDATED("Оновлено"),
        UPDATING("Оновлюється"),
        FAILURE("Помилка оновлення")

    }

    private val _statusFlow = MutableStateFlow(Status.UPDATED)
    private var statusFlow: StateFlow<Status> = _statusFlow.asStateFlow()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()


        setContent {
            HW2_15Theme {
                Column(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(16.dp),
                    verticalArrangement = Arrangement.spacedBy(12.dp)
                ) {
                    Row(
                        horizontalArrangement = Arrangement.spacedBy(8.dp),
                        verticalAlignment = Alignment.CenterVertically
                    ) {
                        SyncNowButton()
                        EnableNightSyncButton()
                    }
                    Box(
                        modifier = Modifier
                            .fillMaxWidth()
                            .height(120.dp),
                        contentAlignment = Alignment.Center
                    ) {
                        StatusText()
                    }

                }
            }
        }
    }


    @Composable
    fun SyncNowButton() {
        val context = LocalContext.current
        Button(onClick = {
            val constraints = Constraints.Builder()
              .setRequiredNetworkType(NetworkType.CONNECTED)
              .build()

            val request = OneTimeWorkRequestBuilder<NewsSyncWorker>()
                .setConstraints(constraints)
                .setInputData(Data.Builder().putString("user_token", "abc123").build())
                .build()

            WorkManager.getInstance(context).enqueueUniqueWork("one_time_sync",
                ExistingWorkPolicy.REPLACE,
                request)

            WorkManager.getInstance(context)
                .getWorkInfoByIdLiveData(request.id)
                .observe(this) { workInfo ->
                    if (workInfo != null) {
                        if (workInfo.state == WorkInfo.State.SUCCEEDED) {
                            val message = workInfo.outputData.getString("result")
                            _statusFlow.update { Status.UPDATED }
                        }
                        _statusFlow.update {
                            when (workInfo.state) {
                                WorkInfo.State.SUCCEEDED -> Status.UPDATED
                                WorkInfo.State.ENQUEUED -> Status.ENQUEUED
                                WorkInfo.State.RUNNING -> Status.UPDATING
                                WorkInfo.State.FAILED -> Status.FAILURE
                                else -> Status.FAILURE
                            }
                        }


                    }
                }
        } ) {
            Text("Синхронізувати зараз")
        }
    }

    @Composable
    fun EnableNightSyncButton() {
        val context = LocalContext.current
        Button(onClick = {
            val constraints = Constraints.Builder()
                .setRequiredNetworkType(NetworkType.CONNECTED)
                .setRequiresCharging(true)
                .build()

            val request = PeriodicWorkRequestBuilder<NewsSyncWorker>(15, TimeUnit.MINUTES)
                .setConstraints(constraints)
                .setInputData(Data.Builder().putString("user_token", "abc123").build())
                .build()

            WorkManager.getInstance(context).enqueueUniquePeriodicWork("night_news_sync",
                ExistingPeriodicWorkPolicy.KEEP,
                request)

            WorkManager.getInstance(context)
                .getWorkInfoByIdLiveData(request.id)
                .observe(this) { workInfo ->
                    if (workInfo != null) {
                        if (workInfo.state == WorkInfo.State.SUCCEEDED) {
                            val message = workInfo.outputData.getString("result")
                            _statusFlow.update { Status.UPDATED }
                        }
                        _statusFlow.update {
                            when (workInfo.state) {
                                WorkInfo.State.SUCCEEDED -> Status.UPDATED
                                WorkInfo.State.ENQUEUED -> Status.ENQUEUED
                                WorkInfo.State.RUNNING -> Status.UPDATING
                                WorkInfo.State.FAILED -> Status.FAILURE
                                else -> Status.FAILURE
                            }
                        }


                    }
                }


        }) {
            Text("Увімкнути нічну синхронізацію")
        }
    }

    @Composable
    fun StatusText() {
        val status by statusFlow.collectAsState()
        Text(status.string)
    }
}


