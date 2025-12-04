# Singleton Method Design Pattern

![](https://media.geeksforgeeks.org/wp-content/uploads/20250901130421008013/client_a.webp)

## 1. What is the Singleton Design Pattern?

**Definition:**
The **Singleton Pattern** ensures that **only one instance** of a class exists throughout the lifetime of an application, and provides a **global point of access** to it.

---

## 2. Why Use Singleton?

Because certain resources must be controlled globally and efficiently.

**Example use cases:**

* Database connection pool (only one connection manager)
* Logger (single logging interface)
* Configuration manager
* Thread pool manager
* Cache or printer spooler

---

## 3. Key Concepts in Singleton Pattern


| Component                   | Description                               |
| --------------------------- | ----------------------------------------- |
| **Private Constructor**     | Prevents external instantiation.          |
| **Static Instance Pointer** | Stores the only instance of the class.    |
| **Public Static Method**    | Provides global access point.             |
| **Thread Safety**           | Must ensure in multithreaded environment. |

![](https://media.geeksforgeeks.org/wp-content/uploads/20250923104626003542/stack_memory.webp)

---

## 4. Implementations in C++

Let’s go step-by-step through all variants:

---

### 🧩 1. Classic (Lazy Initialization)

> Instance is created only when needed.

```cpp
#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;  // static instance pointer
    Singleton() { cout << "Instance Created\n"; } // private constructor

public:
    static Singleton* getInstance() {
        if (instance == nullptr)
            instance = new Singleton();
        return instance;
    }

    void doSomething() {
        cout << "Doing work...\n";
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout << (s1 == s2 ? "Same Instance\n" : "Different Instances\n");
    s1->doSomething();
}
```

**Output:**

```
Instance Created
Same Instance
Doing work...
```

🧠 *Issue:* Not thread-safe — multiple threads could create multiple instances.

---

### 🧩 2. Thread-Safe Singleton (Synchronized Access)

> Use a mutex to protect instance creation.

```cpp
#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;
    Singleton() { cout << "Instance Created\n"; }

public:
    static Singleton* getInstance() {
        lock_guard<mutex> lock(mtx);  // Thread-safe block
        if (instance == nullptr)
            instance = new Singleton();
        return instance;
    }

    void doSomething() { cout << "Thread-Safe Singleton Working\n"; }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton::getInstance()->doSomething();
}
```

🧠 *Note:* Thread-safe, but performance overhead due to locking every call.

---

### 🧩 3. Eager Initialization

> Instance is created **at program start**, even if not used.

```cpp
#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    Singleton() { cout << "Instance Created (Eager)\n"; }

public:
    static Singleton* getInstance() {
        return instance;
    }

    void doSomething() { cout << "Eager Singleton Working\n"; }
};

// Initialize eagerly
Singleton* Singleton::instance = new Singleton();

int main() {
    Singleton::getInstance()->doSomething();
}
```

🧠 *Use when:* Singleton is lightweight and always needed.

---

### 🧩 4. Double-Checked Locking (Efficient Thread-Safe)

> Combines lazy init with minimal locking.

```cpp
#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;
    Singleton() { cout << "Instance Created (DCL)\n"; }

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr)
                instance = new Singleton();
        }
        return instance;
    }

    void doSomething() { cout << "Double-Checked Locking Working\n"; }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton::getInstance()->doSomething();
}
```

🧠 *Best balance* between safety and performance.

---

### 🧩 5. Static Local Variable (C++11 and later — Best Way)

> Thread-safe lazy initialization guaranteed by C++11 standard.

```cpp
#include <iostream>
using namespace std;

class Singleton {
private:
    Singleton() { cout << "Instance Created (Static Local)\n"; }
    ~Singleton() {}

public:
    Singleton(const Singleton&) = delete;            // Prevent copy
    Singleton& operator=(const Singleton&) = delete; // Prevent assignment

    static Singleton& getInstance() {
        static Singleton instance; // Created once, thread-safe
        return instance;
    }

    void doSomething() { cout << "Static Local Singleton Working\n"; }
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    cout << (&s1 == &s2 ? "Same Instance\n" : "Different\n");
    s1.doSomething();
}
```

✅ **Advantages:**

* Thread-safe by default (since C++11)
* Lazy initialization
* Clean and simple

---

## 5. Real-World Example (Logger)

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
private:
    ofstream logFile;
    Logger() { logFile.open("log.txt", ios::app); }

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const string& msg) {
        logFile << msg << endl;
    }

    ~Logger() { logFile.close(); }

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
};

int main() {
    Logger::getInstance().log("Application started");
    Logger::getInstance().log("Something happened");
}
```

---

## 6. Key Takeaways

| Variant        | Thread Safe | Lazy | Recommended? | Notes                      |
| -------------- | ----------- | ---- | ------------ | -------------------------- |
| Classic        | ❌           | ✅    | ❌            | Not thread-safe            |
| Thread-Safe    | ✅           | ✅    | ⚠️           | Slight performance cost    |
| Eager          | ✅           | ❌    | ⚠️           | Wastes resources if unused |
| Double-Checked | ✅           | ✅    | ✅            | Complex but efficient      |
| Static Local   | ✅           | ✅    | ✅✅✅          | Best in modern C++         |
