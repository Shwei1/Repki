package com.example.hw2_13

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.channelFlow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class BroadcastViewModel(application: Application) : AndroidViewModel(application) {
    private val repository = BroadcastRepository(application.applicationContext)

    private val _events = MutableStateFlow<List<BroadcastEvent>>(emptyList())

    val events: StateFlow<List<BroadcastEvent>> = channelFlow {
        launch {
            repository.observeEvents().collect { event ->
                _events.update { listOf(event) + it }
            }
        }
        _events.collect { send(it) }
    }.stateIn(
        scope = viewModelScope,
        started = SharingStarted.WhileSubscribed(5_000),
        initialValue = emptyList()
    )

    fun deleteEvent(event: BroadcastEvent) = _events.update { it - event }

    fun clearAll() {
        _events.value = emptyList()
    }
}
