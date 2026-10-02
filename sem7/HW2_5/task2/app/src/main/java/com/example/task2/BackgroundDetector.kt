package com.example.task2

import android.app.Activity
import android.app.Application
import android.os.Bundle
import androidx.lifecycle.DefaultLifecycleObserver
import androidx.lifecycle.LifecycleOwner
import timber.log.Timber

class BackgroundDetector : DefaultLifecycleObserver {
    override fun onStart(owner: LifecycleOwner) {
        Timber.d("Застосунок перейшов у FOREGROUND (видимий на екрані)")
    }

    override fun onStop(owner: LifecycleOwner) {
        Timber.d("Застосунок перейшов у BACKGROUND (згорнутий у фон)")
    }




}