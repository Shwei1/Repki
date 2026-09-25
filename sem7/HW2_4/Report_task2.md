# Завдання 2


1. Сценарій А
```
2026-09-25 19:49:57.269  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onCreate() викликано
2026-09-25 19:49:57.279  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onStart() викликано
2026-09-25 19:49:57.293  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onResume() викликано
```

2. Сценарій Б
   Згорнули програму:
   ```
   2026-09-25 19:52:40.098  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onPause() викликано
   2026-09-25 19:52:40.100  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onStop() викликано
   ```
   Повернулися в програму з недавніх:
   ```
   2026-09-25 19:54:58.766  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onStart() викликано
   2026-09-25 19:54:58.769  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onResume() викликано
   ```
3. Сценарій В
   ```
   2026-09-25 19:56:13.439  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onPause() викликано
   2026-09-25 19:56:13.441  3507-3507  VRI[MainActivity]       com.example.task2                    D  visibilityChanged oldVisibility=true newVisibility=false
   2026-09-25 19:56:13.494  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onStop() викликано
   2026-09-25 19:56:13.509  3507-3507  MainActivity            com.example.task2                    D  MainActivity: onDestroy() викликано
   ```

4. Сценарій Г
   ```
   2026-09-25 19:57:48.914  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onPause() викликано
   2026-09-25 19:57:48.921  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onStop() викликано
   2026-09-25 19:57:48.940  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onDestroy() викликано
   2026-09-25 19:57:48.977  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onCreate() викликано
   2026-09-25 19:57:48.978  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onStart() викликано
   2026-09-25 19:57:48.979  3770-3770  MainActivity            com.example.task2                    D  MainActivity: onResume() викликано
   2026-09-25 19:57:49.013  3770-3770  VRI[MainActivity]       com.example.task2                    D  WindowInsets changed: 1280x720 statusBars:[0,48,0,0] navigationBars:[0,0,0,48] mandatorySystemGestures:[0,48,0,64] 
   ```



## Друга активність

```
2026-09-25 20:28:42.654  4348-4348  MainActivity            com.example.task2                    D  MainActivity: onPause() викликано
2026-09-25 20:28:42.664  4348-4348  SecondActivity          com.example.task2                    D  SecondActivity: onCreate () викликано
2026-09-25 20:28:42.665  4348-4348  SecondActivity          com.example.task2                    D  SecondActivity: onStart() викликано
2026-09-25 20:28:42.666  4348-4348  SecondActivity          com.example.task2                    D  SecondActivity: onResume() викликано
2026-09-25 20:28:43.286  4348-4348  MainActivity            com.example.task2                    D  MainActivity: onStop() викликано
```

Спочатку повністю запускається друга активність, і лише після її повної ініціалізації (при resume користувач уже може з нею взаємодіяти) закривається перша активність.
Інакше, якби спочатку закривалася перша активність, могло б статися так, що друга активність коректно не ініціалізувалася, а повертатися від неї вже нема куди. Програма лишається без жодної активності і, певно, крашиться.
