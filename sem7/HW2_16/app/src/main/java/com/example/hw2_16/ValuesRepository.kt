package com.example.hw2_16

import androidx.datastore.core.DataStore
import androidx.datastore.preferences.core.Preferences
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.core.intPreferencesKey
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.map

class ValuesRepository(private val dataStore: DataStore<Preferences>) {

    private val notificationAmountKey = intPreferencesKey("NOTIFICATIONS_SENT")

    var notificationAmount: Flow<Int> = dataStore.data.map {
        it[notificationAmountKey] ?: 0
    }

    suspend fun incrementNotifications() {
        dataStore.edit { prefs ->
            val current = prefs[notificationAmountKey] ?: 0
            prefs[notificationAmountKey] = current + 1
        }
    }
}