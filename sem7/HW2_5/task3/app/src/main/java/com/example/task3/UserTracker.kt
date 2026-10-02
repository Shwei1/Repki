package com.example.task3

import android.content.Context

object UserTracker {
    private val listeners = mutableListOf<Context>()

    fun register(context: Context) {
        listeners.add(context.applicationContext);
    }

//    fun unregister(context: Context) {
//        listeners.remove(context)
//    }

    fun getListenersCount(): Int = listeners.size
}