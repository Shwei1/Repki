package com.example.task2

import android.app.Application
import androidx.lifecycle.ProcessLifecycleOwner
import timber.log.Timber

class MyApp: Application() {

    override fun onCreate() {
        super.onCreate()

        if (BuildConfig.DEBUG) {
            Timber.plant(Timber.DebugTree())
        }

        ProcessLifecycleOwner.get().lifecycle.addObserver(BackgroundDetector())
    }
}