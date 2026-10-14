package com.example.hw2_9

import android.os.Bundle
import android.widget.Button
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.delay
import kotlinx.coroutines.ensureActive
import kotlinx.coroutines.launch
import kotlinx.coroutines.supervisorScope
import timber.log.Timber

class MainActivity : AppCompatActivity() {

    var calculationJob: Job? = null

    val ceh = CoroutineExceptionHandler { _, throwable ->
        Timber.e("Глобальне перехоплення крашу: ${throwable.message}")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.btnStart).setOnClickListener { handleBtnStart() }
        findViewById<Button>(R.id.btnCancel).setOnClickListener { handleBtnCancel() }
        findViewById<Button>(R.id.btnTestCrash).setOnClickListener { handleBtnTestCrash() }
        findViewById<Button>(R.id.btnGlobalCrash).setOnClickListener { handleBtnGlobalCrash() }

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
    }

    fun handleBtnStart() {
        if (calculationJob?.isActive == true) return

        calculationJob = lifecycleScope.launch(Dispatchers.Default) {
            try {
                for (i in 1..100) {
                    Timber.d("Обробка: $i%")
                    Thread.sleep(50)
                    ensureActive()
                }
                Timber.d("Роботу успішно завершено!");
            } catch (e: CancellationException) {
                Timber.d("Обробку скасовано користувачем");
                throw e
            }
        }
    }

    fun handleBtnCancel() {
        if (calculationJob?.isActive == true) calculationJob?.cancel()
    }

    fun handleBtnTestCrash() {
        lifecycleScope.launch(Dispatchers.Default) {
            launch(ceh) {
                throw RuntimeException("Вкладений краш!")
            }

            supervisorScope {
                delay(1000)
                try {
                    throw RuntimeException("Банер не завантажився!")
                } catch (e: Exception) {
                    Timber.e("Банер не вдалося завантажити")
                }

            }

            supervisorScope {
                delay(2000)
                Timber.d("Стрічка новий завантажена")
            }
        }
    }

    fun handleBtnGlobalCrash() {
        val safeScope = CoroutineScope(SupervisorJob() + Dispatchers.Main + ceh)
        safeScope.launch {
            delay(500);
            throw IllegalArgumentException("Ой!")
        }
    }
}