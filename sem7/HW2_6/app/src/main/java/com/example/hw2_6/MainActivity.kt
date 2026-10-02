package com.example.hw2_6

import android.os.Bundle
import android.view.inputmethod.EditorInfo
import androidx.activity.ComponentActivity
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.hw2_6.databinding.ActivityMainBinding

class MainActivity : ComponentActivity() {

    private lateinit var binding: ActivityMainBinding
    private val viewModel: TimerViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        viewModel.timerLiveData.observe(this) { binding.tvTimer.text = it.toString() }
        binding.btnStart.setOnClickListener {
            val userSeconds = binding.etSeconds.text.toString().toLongOrNull()
            viewModel.startTimer(userSeconds)
        }
        binding.btnReset.setOnClickListener {
            val userSeconds = binding.etSeconds.text.toString().toLongOrNull()
            viewModel.resetTimer(userSeconds)
        }

        binding.etSeconds.setOnEditorActionListener { _, actionId, _ ->
            if (actionId == EditorInfo.IME_ACTION_DONE) {
                val userSeconds = binding.etSeconds.text.toString().toLongOrNull()
                viewModel.startTimer(userSeconds)
            }
            false
        }

        viewModel.isTimerRunning.observe(this) { isRunning ->
            binding.btnStart.isEnabled = !isRunning
        }
    }
}