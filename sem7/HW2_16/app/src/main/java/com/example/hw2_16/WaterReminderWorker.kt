package com.example.hw2_16

import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.content.Context.NOTIFICATION_SERVICE
import androidx.core.app.NotificationCompat
import androidx.work.CoroutineWorker
import androidx.work.WorkerParameters

class WaterReminderWorker(
    context: Context,
    params: WorkerParameters
) : CoroutineWorker(context, params) {

    override suspend fun doWork(): Result {
        val manager = applicationContext.getSystemService(NOTIFICATION_SERVICE) as NotificationManager
        createNotificationChannel(manager)
        val notification = NotificationCompat.Builder(applicationContext, "water_channel")
            .setContentTitle("Трекер води")
            .setContentText("Час випити склянку води! 💧")
            .setSmallIcon(R.drawable.ic_water_drop)
            .build()

        manager.notify(System.currentTimeMillis().toInt(), notification)
        return Result.success()
    }

    private fun createNotificationChannel(manager: NotificationManager) {
        val channelId = "water_channel"
        val channelName = "Фоновий таймер"
        val channel = NotificationChannel(
            channelId,
            channelName,
            NotificationManager.IMPORTANCE_HIGH
        )
        manager.createNotificationChannel(channel)
    }
}