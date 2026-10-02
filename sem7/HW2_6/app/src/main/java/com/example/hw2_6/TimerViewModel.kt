package com.example.hw2_6

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class TimerViewModel : ViewModel() {
    private val model = TimerModel()
    private val _timerLiveData = MutableLiveData<Long>(30)

    private val _isTimerRunning = MutableLiveData<Boolean>(false)
    val isTimerRunning = _isTimerRunning
    val timerLiveData: LiveData<Long> = _timerLiveData



    fun startTimer(userSeconds: Long?) {
        val seconds = if (userSeconds == null || userSeconds <= 0) 30 else userSeconds

        _timerLiveData.value = seconds
        _isTimerRunning.value = true
        model.start(seconds,
            tick = { _timerLiveData.value = it },
            finish = {
                _timerLiveData.value = 0
                _isTimerRunning.value = false
            })
    }


    fun resetTimer(userSeconds: Long?) = startTimer(userSeconds)

    override fun onCleared() { model.stop() }
}