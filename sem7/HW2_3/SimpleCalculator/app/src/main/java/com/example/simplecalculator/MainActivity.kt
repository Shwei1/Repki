package com.example.simplecalculator

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {

    private val TAG = "SimpleCalculator"

    private lateinit var etFirst: EditText
    private lateinit var etSecond: EditText
    private lateinit var tvResult: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
       }

        etFirst = findViewById(R.id.etFirst)
        etSecond = findViewById(R.id.etSecond)
        tvResult = findViewById(R.id.tvResult)

        findViewById< Button>(R.id.btnAdd).setOnClickListener { calculate('+') }
        findViewById<Button>(R.id.btnSub).setOnClickListener { calculate('-') }
        findViewById<Button>(R.id.btnMul).setOnClickListener { calculate('*') }
        findViewById<Button>(R.id.btnDiv).setOnClickListener { calculate('/') }
        findViewById<Button>(R.id.btnClear).setOnClickListener { clearTexts() }
    }

    private fun calculate(op: Char) {
        val a = etFirst.text.toString().toDoubleOrNull()
        val b = etSecond.text.toString().toDoubleOrNull()

        if (a == null || b == null) {
            Log.w(TAG, "Bad input for '$op'")
            tvResult.text = "Помилка: введіть два числа"
            return
        }

        if (op == '/' && b == 0.0) {
            Log.w(TAG, "Division by zero: $a / $b")
            tvResult.text = "Помилка: ділення на нуль"
            return
        }

        val result = when (op) {
            '+' -> a + b
            '-' -> a - b
            '*' -> a * b
            else -> a / b
        }

        Log.d(TAG, "$a $op $b = $result")
        tvResult.text = when {
            (result % 1.0 == 0.0) -> "Результат: ${result.toLong()}"
            else -> "Результат: $result"
        }
    }

    private fun clearTexts() {
        Log.d(TAG, "Clear pressed")
        etFirst.text.clear()
        etSecond.text.clear()
        tvResult.text = "Результат: "
    }


}