package com.example.hw2_13

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.os.Bundle
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import java.util.UUID

data class BroadcastEvent(val id: String, val type: String, val timestamp: String, val details: String)

val BroadcastEvent.title: String
    get() = when (type) {
        Intent.ACTION_POWER_CONNECTED -> "Charger connected"
        Intent.ACTION_POWER_DISCONNECTED -> "Charger disconnected"
        Intent.ACTION_AIRPLANE_MODE_CHANGED -> "Airplane mode changed"
        Intent.ACTION_BATTERY_LOW -> "Battery low"
        Intent.ACTION_HEADSET_PLUG -> "Headset plugged / unplugged"
        else -> type.substringAfterLast('.')
    }

val BroadcastEvent.description: String
    get() = when (type) {
        Intent.ACTION_POWER_CONNECTED -> "External power was connected to the device. The battery is now charging."
        Intent.ACTION_POWER_DISCONNECTED -> "External power was disconnected. The device is running on battery."
        Intent.ACTION_AIRPLANE_MODE_CHANGED -> "Airplane mode was toggled. The \"state\" extra is true when it was turned on."
        Intent.ACTION_BATTERY_LOW -> "The battery level dropped to a critical value. Consider connecting a charger."
        Intent.ACTION_HEADSET_PLUG -> "A wired headset was plugged in or out. The \"state\" extra is 1 when plugged in."
        else -> "Unknown system event."
    }

class BroadcastRepository(private val context: Context) {

    fun observeEvents(): Flow<BroadcastEvent> = callbackFlow {
        val receiver = object : BroadcastReceiver() {
            override fun onReceive(context: Context, intent: Intent) {
                val event = BroadcastEvent(
                    id = UUID.randomUUID().toString(),
                    type = intent.action ?: "UNKNOWN",
                    timestamp = SimpleDateFormat("dd.MM.yyyy HH:mm:ss.SSS", Locale.getDefault())
                        .format(Date()),
                    details = intent.extras?.format() ?: "No extras"
                )
                trySend(event)
            }
        }
        val filter = IntentFilter().apply {
            addAction(Intent.ACTION_POWER_CONNECTED)
            addAction(Intent.ACTION_POWER_DISCONNECTED)
            addAction(Intent.ACTION_AIRPLANE_MODE_CHANGED)
            addAction(Intent.ACTION_BATTERY_LOW)
            addAction(Intent.ACTION_HEADSET_PLUG)
        }

        context.registerReceiver(receiver, filter, Context.RECEIVER_NOT_EXPORTED)

        awaitClose { context.unregisterReceiver(receiver) }
    }

    private fun Bundle.format(): String =
        keySet().joinToString("\n") { key -> "$key = ${get(key)}" }
}
