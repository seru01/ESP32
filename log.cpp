#include "log.h"
#include <stdarg.h>

#define LOG_BUFFER_SIZE 256

// get just the filename from a path
static const char* baseName(const char* path) {
    const char* file = strrchr(path, '/');
    if (file) return file + 1;
    file = strrchr(path, '\\');
    if (file) return file + 1;
    return path;
}

// convert millis() to HH:MM:SS
static void getTimestamp(char* buffer, size_t len) {
    unsigned long ms = millis() / 1000; // seconds
    unsigned long hours = ms / 3600;
    unsigned long minutes = (ms % 3600) / 60;
    unsigned long seconds = ms % 60;
    snprintf(buffer, len, "%02lu:%02lu:%02lu", hours, minutes, seconds);
}

static void logPrint(const char* level, const char* file, int line, const char* fmt, va_list args) {
    char buffer[LOG_BUFFER_SIZE];
    vsnprintf(buffer, LOG_BUFFER_SIZE, fmt, args);

    char ts[16];
    getTimestamp(ts, sizeof(ts));

    Serial.print("[");
    Serial.print(ts);
    Serial.print("]");
    Serial.print("[");
    Serial.print(level);
    Serial.print("][");
    Serial.print(baseName(file));
    Serial.print(":");
    Serial.print(line);
    Serial.print("] ");

    Serial.println(buffer);
}

void Log::error(const char* file, int line, const char* fmt, ...) {
#if LOG_LEVEL >= LOG_ERROR
    va_list args;
    va_start(args, fmt);
    logPrint("ERROR", file, line, fmt, args);
    va_end(args);
#endif
}

void Log::warn(const char* file, int line, const char* fmt, ...) {
#if LOG_LEVEL >= LOG_WARN
    va_list args;
    va_start(args, fmt);
    logPrint("WARN", file, line, fmt, args);
    va_end(args);
#endif
}

void Log::info(const char* file, int line, const char* fmt, ...) {
#if LOG_LEVEL >= LOG_INFO
    va_list args;
    va_start(args, fmt);
    logPrint("INFO", file, line, fmt, args);
    va_end(args);
#endif
}

void Log::debug(const char* file, int line, const char* fmt, ...) {
#if LOG_LEVEL >= LOG_DEBUG
    va_list args;
    va_start(args, fmt);
    logPrint("DEBUG", file, line, fmt, args);
    va_end(args);
#endif
}
