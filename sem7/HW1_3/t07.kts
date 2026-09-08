val rawLogs = listOf(
 "2026-09-01 INFO: User logged in",
 "2026-09-01 ERROR: 500 Internal Server Error",
 "2026-09-01 WARN: High memory usage",
 "2026-09-01 ERROR: 404 Not Found",
 "2026-09-01 INFO: Payment processed"
)

val stats = mutableMapOf<String, Int>()

val errors = mutableListOf<String>()



rawLogs.filter { msg -> when {
    msg.contains("INFO: ") -> { stats["info"] = stats.getOrDefault("info", 0) + 1; true }
    msg.contains("WARN: ") -> { stats["warn"] = stats.getOrDefault("warn", 0) + 1; true }
    msg.contains("ERROR: ") -> { stats["error"] = stats.getOrDefault("error", 0) + 1; errors.add(msg); true }
    else -> false
}}

print("""== Stats ==
Info: ${stats["info"]}
Warnings: ${stats["warn"]}
Errors: ${stats["error"]}
Error messages:
${errors.joinToString("\n")}
""")

