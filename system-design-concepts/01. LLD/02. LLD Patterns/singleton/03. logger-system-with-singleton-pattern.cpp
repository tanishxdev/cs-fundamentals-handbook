#include <iostream>
#include <string>
using namespace std;

// Singleton Logger Class
class Logger {
private:
    static Logger* instance;   // holds the single instance
    Logger() {                 // private constructor
        cout << "Logger Initialized.\n";
    }

public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Static method to access the instance
    static Logger* getInstance() {
        if (instance == nullptr) {
            instance = new Logger();  // create only once
        }
        return instance;
    }

    // Logging function
    void log(const string& message) {
        cout << "[LOG]: " << message << endl;
    }
};

// Initialize static member
Logger* Logger::instance = nullptr;

// ---- Main Function ----
int main() {
    Logger* logger1 = Logger::getInstance();
    logger1->log("Application started");

    Logger* logger2 = Logger::getInstance();
    logger2->log("Processing data...");

    // Prove that both are the same instance
    cout << "Logger1 address: " << logger1 << endl;
    cout << "Logger2 address: " << logger2 << endl;

    return 0;
}
