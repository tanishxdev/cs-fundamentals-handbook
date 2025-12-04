#include <iostream>
#include <string>
using namespace std;

// 🔴 Problem: Logging systems often have multiple levels (INFO, DEBUG, ERROR).
// A single message may be handled differently:
// INFO -> console
// DEBUG -> file
// ERROR -> email alert
// Instead of big if-else chains, use CoR to pass the request until a handler processes it.

// ⚒️ Flow (Dry Run)

// Request 1 (INFO): ConsoleLogger handles ✅
// Request 2 (DEBUG): Console → not handled → FileLogger handles ✅
// Request 3 (ERROR): Console → File → EmailLogger handles ✅

// 🤔 Why Useful

// Avoids if(level == 1) {...} else if(level == 2) {...} mess.
// Easy to add new loggers (e.g., SMSLogger for critical alerts).
// Chain order can be rearranged depending on needs.

// ------------------- Request -------------------
class LogRequest {
public:
    string message;
    int level;  // 1 = INFO, 2 = DEBUG, 3 = ERROR
    LogRequest(string msg, int lvl) : message(msg), level(lvl) {}
};

// ------------------- Abstract Handler -------------------
class Logger {
protected:
    Logger* nextLogger;
public:
    Logger() : nextLogger(nullptr) {}
    void setNext(Logger* next) { nextLogger = next; }

    virtual void logMessage(LogRequest request) {
        if (nextLogger != nullptr)
            nextLogger->logMessage(request);
        else
            cout << "No logger available for message: " << request.message << "\n";
    }
    virtual ~Logger() {}
};

// ------------------- Concrete Handlers -------------------

// INFO level logger (console)
class ConsoleLogger : public Logger {
public:
    void logMessage(LogRequest request) override {
        if (request.level == 1) {
            cout << "[INFO] Console Logger: " << request.message << "\n";
        } else if (nextLogger != nullptr) {
            nextLogger->logMessage(request);
        }
    }
};

// DEBUG level logger (file)
class FileLogger : public Logger {
public:
    void logMessage(LogRequest request) override {
        if (request.level == 2) {
            cout << "[DEBUG] File Logger: " << request.message << " (written to log file)\n";
        } else if (nextLogger != nullptr) {
            nextLogger->logMessage(request);
        }
    }
};

// ERROR level logger (email)
class EmailLogger : public Logger {
public:
    void logMessage(LogRequest request) override {
        if (request.level == 3) {
            cout << "[ERROR] Email Logger: " << request.message 
                 << " (email sent to admin)\n";
        } else if (nextLogger != nullptr) {
            nextLogger->logMessage(request);
        }
    }
};

// ------------------- Client -------------------
int main() {
    // Create loggers
    ConsoleLogger console;
    FileLogger file;
    EmailLogger email;

    // Build Chain: Console -> File -> Email
    console.setNext(&file);
    file.setNext(&email);

    // Requests
    LogRequest req1("System started successfully.", 1);  // INFO
    LogRequest req2("Variable x might be uninitialized.", 2); // DEBUG
    LogRequest req3("Database connection failed!", 3); // ERROR

    console.logMessage(req1); // handled by ConsoleLogger
    console.logMessage(req2); // passed to FileLogger
    console.logMessage(req3); // passed to EmailLogger

    return 0;
}
