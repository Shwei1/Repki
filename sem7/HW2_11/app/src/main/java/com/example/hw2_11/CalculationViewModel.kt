package com.example.hw2_11

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.launch
import timber.log.Timber
import java.math.BigInteger
import kotlin.time.Duration.Companion.milliseconds

class CalculationViewModel : ViewModel() {

    // Cold flow
//    val fib: Flow<BigInteger> = flow {
//        var f1 = BigInteger.ONE
//        var f2 = BigInteger.ONE
//        while (true) {
//            emit(f1)
//            Timber.i("ViewModel: $f1")
//            delay(500.milliseconds)
//            val f = f2 + f1
//            f2 = f1
//            f1 = f
//        }
//    }

    // Hot flow
    var _fib = MutableStateFlow(BigInteger.ONE)
    val fib = _fib.asStateFlow()
    init {
        viewModelScope.launch {
            var f1 = BigInteger.ONE
            var f2 = BigInteger.ONE
            while (true) {
                _fib.emit(f1)
                Timber.i("ViewModel: $f1")
                delay(500.milliseconds)
                val f = f2 + f1
                f2 = f1
                f1 = f

            }
        }
    }

}