package com.example.hw2_8

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import java.util.concurrent.atomic.AtomicInteger
import kotlin.random.Random
import kotlin.concurrent.thread

class DiceViewModel : ViewModel() {

    private val model = DiceModel()
    private val _diceValues = MutableLiveData<List<Int>>((1..6).toList())
    var diceValues: LiveData<List<Int>> = _diceValues

    private val _isRolling = MutableLiveData(false)
    val isRolling = _isRolling

    private val _buttonText = MutableLiveData("ROLL")
    val buttonText = _buttonText

    private var job: Job? = null

    fun rollDice() {
        job?.cancel()

        job = viewModelScope.launch {
            _isRolling.value = true
            _buttonText.value = "RESTART"

            model.rollAll { idx, value ->
                val current = _diceValues.value ?: (1..6).toList()
                _diceValues.value = current.toMutableList()
                    .also { it[idx] = value }
            }

            _isRolling.value = false
            _buttonText.value = "ROLL"
        }



    }

}