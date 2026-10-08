package com.example.hw2_7

import android.media.Image
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {
    private val viewModel: DiceViewModel by viewModels()

    private lateinit var btnRoll: Button
    private lateinit var btnReset: Button
    private lateinit var diceViews: List<ImageView>

    private val diceImages = listOf(R.drawable.die_1, R.drawable.die_2, R.drawable.die_3, R.drawable.die_4, R.drawable.die_5, R.drawable.die_6)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        setContentView(R.layout.activity_main)

        btnRoll = findViewById(R.id.btnRoll)
        btnReset = findViewById(R.id.btnReset)

        diceViews = listOf(
            R.id.die_1, R.id.die_2, R.id.die_3, R.id.die_4, R.id.die_5, R.id.die_6
        ).map { findViewById(it) }

        btnRoll.setOnClickListener { viewModel.rollDice() }
        viewModel.diceValues.observe(this) {
            values -> values.forEachIndexed {
                i, value ->
                diceViews[i].setImageResource(diceImages[value - 1])
            }
        }

        btnReset.setOnClickListener { viewModel.resetDice() }

        viewModel.isRolling.observe(this) {
            isRolling -> btnRoll.isEnabled = !isRolling
        }

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
    }
}