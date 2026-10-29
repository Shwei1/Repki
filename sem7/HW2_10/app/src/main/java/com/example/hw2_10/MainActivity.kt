package com.example.hw2_10

import android.os.Bundle
import android.widget.EditText
import android.widget.ProgressBar
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.isVisible
import androidx.core.widget.doOnTextChanged
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.lifecycleScope
import androidx.lifecycle.repeatOnLifecycle
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {

    private val viewModel: SearchViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val etSearchQuery = findViewById<EditText>(R.id.etSearchQuery)
        val tvSearchResults = findViewById<TextView>(R.id.tvSearchResults)
        val progressBar = findViewById<ProgressBar>(R.id.progressBar)

        etSearchQuery.doOnTextChanged { text, _, _, _ ->
            viewModel.onQueryChanged(text.toString())
        }

        lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.STARTED) {


                launch {
                    viewModel.searchResults.collect {
                        results -> tvSearchResults.text = results.joinToString("\n")
                    }
                }

                launch {
                    viewModel.isLoading.collect {
                        loading -> progressBar.isVisible = loading
                    }
                }
            }
        }

    }
}