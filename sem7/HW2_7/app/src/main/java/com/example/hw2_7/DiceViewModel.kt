package com.example.hw2_7

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import java.util.concurrent.atomic.AtomicInteger
import kotlin.random.Random
import kotlin.concurrent.thread

class DiceViewModel : ViewModel() {
    private val _diceValues = MutableLiveData<List<Int>>((1..6).toList())
    var diceValues: LiveData<List<Int>> = _diceValues

    private val _isRolling = MutableLiveData(false)
    val isRolling = _isRolling

        private var workers: List<Thread> = emptyList()

    fun rollDice() {
        if (_isRolling.value == true) return
        _isRolling.value = true
        val values = (_diceValues.value ?: List(6) { 1 }).toIntArray()
        val remaining = AtomicInteger(6)

        workers = List(6) { i ->
            thread {
                val end = System.currentTimeMillis() + Random.nextInt(1500, 3000)
                try {
                    while (System.currentTimeMillis() < end) {
                        synchronized(values) {
                            values[i] = Random.nextInt(1, 7);
                            _diceValues.postValue(values.toList())
                        }
                        Thread.sleep(100)
                    }
                } catch (e: InterruptedException) {
                    return@thread
                }
                if (remaining.decrementAndGet() == 0) _isRolling.postValue(false)
            }
        }
    }

    fun resetDice() {
        workers.forEach { it.interrupt() }
        _isRolling.postValue(false)
        _diceValues.postValue((1..6).toList())

    }

    override fun onCleared() {
        workers.forEach { it.interrupt() }
    }

}