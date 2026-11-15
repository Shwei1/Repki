package com.example.task2

import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.Service
import android.content.Intent
import android.os.Binder
import android.os.IBinder
import androidx.core.app.NotificationCompat

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.cancel
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.isActive
import kotlinx.coroutines.launch
import timber.log.Timber
import kotlin.time.Duration.Companion.milliseconds

class TimerForegroundService : Service() {

    private val scope: CoroutineScope = CoroutineScope(Dispatchers.Default)

    private var timerJob: Job? = null

    private val _timerSeconds = MutableStateFlow(0)
    var timerSeconds: StateFlow<Int> = _timerSeconds.asStateFlow()

    inner class LocalBinder : Binder() {
        fun getService(): TimerForegroundService = this@TimerForegroundService
    }

    fun getTimerFlow(): StateFlow<Int> = _timerSeconds.asStateFlow()

    private val binder = LocalBinder()

    override fun onBind(intent: Intent?): IBinder {
        return binder
    }

    override fun onCreate() {
        super.onCreate()
        createNotificationChannel()
    }

    override fun onDestroy() {
        scope.cancel()
        super.onDestroy()
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        val notification = createNotification()
        startForeground(1, notification)

        runTimer()

        return START_NOT_STICKY
    }

    private fun createNotification() : Notification {
        val channelId = "timer_channel"

        return NotificationCompat.Builder(this, channelId)
            .setContentTitle("Таймер")
            .setContentText("Таймер іде...")
            .setSmallIcon(R.drawable.ic_launcher_foreground)
            .build()
    }

    private fun createNotificationChannel() {
        val channelId = "timer_channel";
        val channelName = "Фоновий таймер"
        val channel = NotificationChannel(
            channelId,
            channelName,
            NotificationManager.IMPORTANCE_LOW
        )
        val manager = getSystemService(NOTIFICATION_SERVICE) as NotificationManager
        manager.createNotificationChannel(channel)
    }

    private fun runTimer() {
        timerJob?.cancel()
        timerJob = scope.launch {
            while (isActive) {
                Timber.tag("Timer").d("Минуло ${timerSeconds.value} секунд")
                delay(1000.milliseconds)
                _timerSeconds.update{ it + 1 }
            }
        }
    }

    fun stopTimer() {
        timerJob?.cancel()
        timerJob = null
        _timerSeconds.value = 0
        stopForeground(STOP_FOREGROUND_REMOVE)
        stopSelf()
    }
}