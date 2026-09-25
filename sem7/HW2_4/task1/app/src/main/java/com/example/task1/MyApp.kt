package com.example.task1

import android.app.Application
import timber.log.Timber

class MyApp : Application() {

    var taps = 0

    override fun onCreate() {
        super.onCreate()

        if (BuildConfig.DEBUG) {
            Timber.plant(Timber.DebugTree())
        }

        Timber.d("MainActivity успішно запущена!")
    }

}