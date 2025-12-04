# **Singleton Design Pattern (C++)**

---

## **1️⃣ What is it?**

The **Singleton Pattern** ensures:

* ✅ Only **one instance** of a class exists during the program’s lifetime.
* ✅ It provides a **global access point** to that instance.

Think of it as a **“single manager”** that controls one shared resource — for example:

* Only **one Logger** for the whole system
* Only **one Database Connection Pool**
* Only **one Configuration Manager**

---

## **2️⃣ Why do we need it?**

Imagine you have a **Logger class** that writes logs to a file:

* If every function creates its own logger, multiple loggers may write to the same file at once → **corrupted logs**.
* Instead, we want **one single Logger instance** that all parts of the program share safely.

Hence → **Singleton** ensures a **single point of control**.

---

## **3️⃣ How to implement it (Step-by-Step Thinking)**

Let’s go step-by-step slowly and clearly 👇

### 🧩 Step 1: Make the constructor `private`

To **prevent outside code** from creating new instances using `new`.

### 🧩 Step 2: Create a **static pointer** to the single instance

This stores the **only** instance of the class.

### 🧩 Step 3: Create a **public static function** `getInstance()`

This will:

* Create the instance if it doesn’t exist yet.
* Return the existing instance if already created.

---

## **4️⃣ Example: Logger Singleton**

Let’s implement a **Logger** that writes logs to the console.

### ✅ Code:

```cpp
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
```

---

## **5️⃣ Output**

```
Logger Initialized.
[LOG]: Application started
[LOG]: Processing data...
Logger1 address: 0x1234
Logger2 address: 0x1234
```

👉 Notice that both `logger1` and `logger2` have the **same memory address**, meaning only **one object** exists.

---

## **6️⃣ Why it works**

* `private` constructor → nobody can create another object.
* `static instance` → only one memory copy exists.
* `getInstance()` → controlled access.

---

## **7️⃣ Pros ✅**

| Benefit                 | Description                                                 |
| ----------------------- | ----------------------------------------------------------- |
| **Single Control**      | One shared object across app (e.g., one logger, one config) |
| **Lazy Initialization** | Created only when needed                                    |
| **Global Access**       | Easily accessible anywhere                                  |
| **Memory Efficient**    | Prevents redundant object creation                          |

---

## **8️⃣ Cons ❌**

| Drawback                 | Description                                                              |
| ------------------------ | ------------------------------------------------------------------------ |
| **Hidden Dependencies**  | Makes testing harder (since it’s global)                                 |
| **Thread Safety Issues** | In multithreading, multiple instances can be created if not synchronized |
| **Difficult to Extend**  | Once global, hard to replace/mock                                        |
| **Tight Coupling**       | Components depend on a single shared instance                            |

---

## **9️⃣ Thread-Safe Version (Advanced)**

If multiple threads might access it, use a **mutex lock**:

```cpp
#include <mutex>

class SafeLogger {
private:
    static SafeLogger* instance;
    static mutex mtx;
    SafeLogger() {}

public:
    SafeLogger(const SafeLogger&) = delete;
    SafeLogger& operator=(const SafeLogger&) = delete;

    static SafeLogger* getInstance() {
        lock_guard<mutex> lock(mtx); // ensures one thread at a time
        if (instance == nullptr) {
            instance = new SafeLogger();
        }
        return instance;
    }

    void log(const string& msg) {
        cout << "[SafeLog]: " << msg << endl;
    }
};

SafeLogger* SafeLogger::instance = nullptr;
mutex SafeLogger::mtx;
```

---

## **🔟 Real-World Use Cases**

| Use Case                         | Description                      |
| -------------------------------- | -------------------------------- |
| 🧾 **Logger**                    | One logger for the entire system |
| 🗄️ **Database Connection Pool** | One global connection manager    |
| ⚙️ **Configuration Manager**     | Central config file access       |
| 🖨️ **Printer Spooler**          | Only one queue for print jobs    |
| 🧠 **Cache Manager**             | Shared in-memory cache           |

---

## **💬 Summary Table**

| Concept                  | Description                                    |
| ------------------------ | ---------------------------------------------- |
| **Pattern Type**         | Creational                                     |
| **Goal**                 | Ensure one instance only                       |
| **Access**               | Via static `getInstance()`                     |
| **Initialization Types** | Lazy, Eager, Double-Checked, Thread-Safe, etc. |
| **Common Example**       | Logger, Database Manager, Config Loader        |

---

## **🪄 Takeaway Thought**

> Singleton is like the “Captain of the ship.”
> There’s only **one captain** managing everything,
> and everyone (other objects) must go through him for control.

---