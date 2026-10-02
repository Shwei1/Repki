package com.example.hw2_6

import android.os.CountDownTimer

class TimerModel {
    private var timer: CountDownTimer? = null

    fun start(seconds: Long, tick: (Long) -> Unit, finish: () -> Unit) {
        timer?.cancel()
        timer = object : CountDownTimer(seconds * 1000, 1000) {
            override fun onTick(ms: Long) = tick((ms + 999) / 1000)
            override fun onFinish() = finish()
        }.start()
    }

    fun stop() { timer?.cancel(); timer = null }
}
