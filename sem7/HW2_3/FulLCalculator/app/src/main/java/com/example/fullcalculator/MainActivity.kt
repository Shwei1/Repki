package com.example.fullcalculator

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.fullcalculator.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var decimalPlaced: Boolean = false
    private var recordedResult: String? = null
    private var currentOperand: String? = null
    private var currentOp: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(binding.main) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val digits = listOf(
            binding.btn0, binding.btn1, binding.btn2, binding.btn3, binding.btn4,
            binding.btn5, binding.btn6, binding.btn7, binding.btn8, binding.btn9
        )
        for (button in digits) {
            button.setOnClickListener { onDigit(button.text.toString()) }
        }
        binding.btnAdd.setOnClickListener { onOperation("+") }
        binding.btnSub.setOnClickListener { onOperation("-") }
        binding.btnMul.setOnClickListener { onOperation("*") }
        binding.btnDiv.setOnClickListener { onOperation("/") }
        binding.btnEquals.setOnClickListener { onEquals() }
        binding.btnClear.setOnClickListener { onClear() }
        binding.btnDot.setOnClickListener { onDot() }
        binding.btnBack.setOnClickListener { onBackspace() }
    }

    private fun clearDisplay() {
        binding.tvDisplay.text = "";
    }

    private fun onDigit(digit: String) {
        val currentText = currentOperand ?: "";
        currentOperand = if (currentText == "0") digit else currentText + digit
        binding.tvDisplay.text = currentOperand
    }

    private fun onOperation(op: String) {
        if (currentOperand == null) {

            if (recordedResult != null) currentOp = op
            return
        }
        if (currentOp != null) {
            return
        }
        recordedResult = currentOperand
        currentOp = op
        currentOperand = null
        decimalPlaced = false
        clearDisplay() // but not vars
    }

    private fun onEquals() {
        val op1 = recordedResult?.toDoubleOrNull()
        val op2 = currentOperand?.toDoubleOrNull()
        val op = currentOp
        if (op1 == null || op2 == null || op == null) {
            return
        }

        if (op == "/" && op2 == 0.0) {
            onClear()
            binding.tvDisplay.text = "Помилка"
            return
        }

        val result = when (op) {
            "+" -> op1 + op2
            "-" -> op1 - op2
            "*" -> op1 * op2
            else -> op1 / op2
        }
        val text = if (result % 1.0 == 0.0) result.toLong().toString() else result.toString()

        binding.tvDisplay.text = text
        currentOperand = text
        recordedResult = null
        currentOp = null
        decimalPlaced = text.contains('.')
    }

    private fun onClear() {
        recordedResult = null
        currentOperand = null
        currentOp = null
        decimalPlaced = false
        binding.tvDisplay.text = "0"
    }

    private fun onDot() {
        if (decimalPlaced) return
        currentOperand = (currentOperand ?: "0") + "."
        decimalPlaced = true
        binding.tvDisplay.text = currentOperand
    }

    private fun onBackspace() {
        val current = currentOperand ?: return
        if (current.endsWith('.')) decimalPlaced = false
        currentOperand = current.dropLast(1).ifEmpty { null }
        binding.tvDisplay.text = currentOperand ?: "0"
    }
}