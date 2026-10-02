package com.example.task1
import android.app.Activity
import android.app.Application
import android.os.Bundle
import timber.log.Timber

class MyApp : Application() {

    override fun onCreate() {
        super.onCreate()

        if (BuildConfig.DEBUG) {
            Timber.plant(Timber.DebugTree())
        }

        registerActivityLifecycleCallbacks(object : ActivityLifecycleCallbacks {

            override fun onActivityCreated(activity: Activity, savedInstanceState: Bundle?) {
                log("onActivityCreated", activity)
            }

            override fun onActivityStarted(activity: Activity) {
                log("onActivityStarted", activity)
            }

            override fun onActivityResumed(activity: Activity) {
                log("onActivityResumed", activity)
            }

            override fun onActivityPaused(activity: Activity) {
                log("onActivityPaused", activity)
            }

            override fun onActivityStopped(activity: Activity) {
                log("onActivityStopped", activity)
            }

            override fun onActivityDestroyed(activity: Activity) {
                log("onActivityDestroyed", activity)
            }

            override fun onActivitySaveInstanceState(activity: Activity, outState: Bundle) {}
        })
    }

    private fun log(event: String, activity: Activity) {
        val state = (activity as? androidx.lifecycle.LifecycleOwner)?.lifecycle?.currentState
        Timber.d("$event: ${activity.javaClass.simpleName}, state = $state")
    }
}