package com.example.hw2_11

import android.os.Bundle
import android.widget.Button
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import timber.log.Timber

class MainActivity : AppCompatActivity() {

    private val viewModel: CalculationViewModel by viewModels()

    private var calculationJob: Job? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val btnSubscribe = findViewById<Button>(R.id.btnSubscribe)
        val btnCancel = findViewById<Button>(R.id.btnCancel)

        btnSubscribe.setOnClickListener {
            if (calculationJob?.isActive == true) return@setOnClickListener

            calculationJob = lifecycleScope.launch {
                Timber.d("Subscribed")
                viewModel.fib.collect { value ->
                    Timber.d("fib: %s", value)
                }
                Timber.d("Completed")
            }
        }

        btnCancel.setOnClickListener {
            calculationJob?.cancel()
            calculationJob = null
            Timber.d("Cancelled")
        }
    }
}
