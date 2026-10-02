#   Завдання №1

## Частина 1

У logcat:
```
2026-09-25 20:35:11.918  4779-4779  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо призупинено
2026-09-25 20:35:24.432  4779-4779  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо відновлено
```


# Частина 2

```
2026-09-25 20:46:38.048  5006-5006  AnalyticsTracker        com.example.task1                    D  AnalyticsTracker: Екран втратив фокус (ON_PAUSE)
2026-09-25 20:46:38.051  5006-5006  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо призупинено
2026-09-25 20:46:38.068  5006-5006  MyApp                   com.example.task1                    D  onActivityStopped: MainActivity, state = CREATED
2026-09-25 20:47:07.095  5006-5006  MyApp                   com.example.task1                    D  onActivityStarted: MainActivity, state = CREATED
2026-09-25 20:47:07.095  5006-5006  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо відновлено
2026-09-25 20:47:07.096  5006-5006  MyApp                   com.example.task1                    D  onActivityResumed: MainActivity, state = STARTED
2026-09-25 20:47:07.096  5006-5006  AnalyticsTracker        com.example.task1                    D  AnalyticsTracker: Користувач взаємодіє з екраном (ON_RESUME)
```

# Частина 3

Відкриваємо другий екран:
```
2026-09-25 21:02:13.206  5280-5280  AnalyticsTracker        com.example.task1                    D  AnalyticsTracker: Екран втратив фокус (ON_PAUSE)
2026-09-25 21:02:13.206  5280-5280  MyApp                   com.example.task1                    D  onActivityPaused: MainActivity, state = STARTED
2026-09-25 21:02:13.214  5280-5280  MyApp                   com.example.task1                    D  onActivityCreated: SecondActivity, state = INITIALIZED
2026-09-25 21:02:13.216  5280-5280  MyApp                   com.example.task1                    D  onActivityStarted: SecondActivity, state = CREATED
2026-09-25 21:02:13.217  5280-5280  MyApp                   com.example.task1                    D  onActivityResumed: SecondActivity, state = STARTED
2026-09-25 21:02:13.807  5280-5280  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо призупинено
2026-09-25 21:02:13.827  5280-5280  MyApp                   com.example.task1                    D  onActivityStopped: MainActivity, state = CREATED

```

Повертаємось на перший
```
2026-09-25 21:04:43.179  5280-5280  MyApp                   com.example.task1                    D  onActivityPaused: SecondActivity, state = STARTED
2026-09-25 21:04:43.190  5280-5280  MyApp                   com.example.task1                    D  onActivityStarted: MainActivity, state = CREATED
2026-09-25 21:04:43.191  5280-5280  AudioPlayer             com.example.task1                    D  AudioPlayer: Відтворення фонового аудіо відновлено
2026-09-25 21:04:43.191  5280-5280  MyApp                   com.example.task1                    D  onActivityResumed: MainActivity, state = STARTED
2026-09-25 21:04:43.192  5280-5280  AnalyticsTracker        com.example.task1                    D  AnalyticsTracker: Користувач взаємодіє з екраном (ON_RESUME)
2026-09-25 21:04:43.719  5280-5280  MyApp                   com.example.task1                    D  onActivityStopped: SecondActivity, state = CREATED
2026-09-25 21:04:43.729  5280-5280  MyApp                   com.example.task1                    D  onActivityDestroyed: SecondActivity, state = DESTROYED
```
