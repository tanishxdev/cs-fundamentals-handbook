#include <iostream>
#include <mutex>
using namespace std;

/*
============================================================
1. BASIC LAZY SINGLETON (NOT THREAD SAFE)
------------------------------------------------------------
- Instance created only when getInstance() is called.
- Not safe in multithreaded environment.
- Multiple threads may create multiple instances.
============================================================
*/
class SingletonLazy {
private:
    static SingletonLazy* instance;   // Static instance pointer

    // Private constructor prevents direct object creation
    SingletonLazy() {
        cout << "[Lazy] Instance Created\n";
    }

public:
    static SingletonLazy* getInstance() {
        if (instance == nullptr) {
            instance = new SingletonLazy();
        }
        return instance;
    }

    void doSomething() {
        cout << "[Lazy] Doing work...\n";
    }
};

SingletonLazy* SingletonLazy::instance = nullptr;


/*
============================================================
2. THREAD-SAFE SINGLETON USING MUTEX
------------------------------------------------------------
- Uses mutex to protect critical section.
- Ensures only one instance is created even in multithreading.
- Slight performance cost due to locking each time.
============================================================
*/
class SingletonThreadSafe {
private:
    static SingletonThreadSafe* instance;
    static mutex mtx;

    SingletonThreadSafe() {
        cout << "[ThreadSafe] Instance Created\n";
    }

public:
    static SingletonThreadSafe* getInstance() {
        lock_guard<mutex> lock(mtx);  // Thread safety
        if (instance == nullptr) {
            instance = new SingletonThreadSafe();
        }
        return instance;
    }

    void doSomething() {
        cout << "[ThreadSafe] Working safely...\n";
    }
};

SingletonThreadSafe* SingletonThreadSafe::instance = nullptr;
mutex SingletonThreadSafe::mtx;


/*
============================================================
3. EAGER SINGLETON
------------------------------------------------------------
- Instance created at program startup.
- No delay, no checks, always available.
- Wastes memory if never used.
============================================================
*/
class SingletonEager {
private:
    static SingletonEager* instance;

    SingletonEager() {
        cout << "[Eager] Instance Created\n";
    }

public:
    static SingletonEager* getInstance() {
        return instance;
    }

    void doSomething() {
        cout << "[Eager] Working...\n";
    }
};

// Instance created before main() starts
SingletonEager* SingletonEager::instance = new SingletonEager();


/*
============================================================
4. DOUBLE-CHECKED LOCKING SINGLETON
------------------------------------------------------------
- Reduces locking overhead.
- First check without lock, second inside lock.
- Efficient but risky before C++11 memory model fixes.
============================================================
*/
class SingletonDCL {
private:
    static SingletonDCL* instance;
    static mutex mtx;

    SingletonDCL() {
        cout << "[DCL] Instance Created\n";
    }

public:
    static SingletonDCL* getInstance() {
        if (instance == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new SingletonDCL();
            }
        }
        return instance;
    }

    void doSomething() {
        cout << "[DCL] Working...\n";
    }
};

SingletonDCL* SingletonDCL::instance = nullptr;
mutex SingletonDCL::mtx;


/*
============================================================
5. MODERN C++ SINGLETON (BEST PRACTICE)
------------------------------------------------------------
- Uses static local variable.
- Thread-safe since C++11 automatically.
- Cleanest and safest approach.
============================================================
*/
class SingletonStaticLocal {
private:
    SingletonStaticLocal() {
        cout << "[Static Local] Instance Created\n";
    }

public:
    // Prevent copy and assignment
    SingletonStaticLocal(const SingletonStaticLocal&) = delete;
    SingletonStaticLocal& operator=(const SingletonStaticLocal&) = delete;

    static SingletonStaticLocal& getInstance() {
        static SingletonStaticLocal instance; // Created once
        return instance;
    }

    void doSomething() {
        cout << "[Static Local] Working...\n";
    }
};


/*
============================================================
MAIN FUNCTION — TESTING ALL SINGLETON TYPES
============================================================
*/
int main() {

    cout << "\n--- BASIC LAZY SINGLETON ---\n";
    SingletonLazy* l1 = SingletonLazy::getInstance();
    SingletonLazy* l2 = SingletonLazy::getInstance();
    cout << (l1 == l2 ? "Same Instance\n" : "Different Instances\n");
    l1->doSomething();

    cout << "\n--- THREAD SAFE SINGLETON ---\n";
    SingletonThreadSafe* ts1 = SingletonThreadSafe::getInstance();
    SingletonThreadSafe* ts2 = SingletonThreadSafe::getInstance();
    cout << (ts1 == ts2 ? "Same Instance\n" : "Different Instances\n");
    ts1->doSomething();

    cout << "\n--- EAGER SINGLETON ---\n";
    SingletonEager::getInstance()->doSomething();

    cout << "\n--- DOUBLE CHECKED LOCKING ---\n";
    SingletonDCL* d1 = SingletonDCL::getInstance();
    SingletonDCL* d2 = SingletonDCL::getInstance();
    cout << (d1 == d2 ? "Same Instance\n" : "Different Instances\n");
    d1->doSomething();

    cout << "\n--- STATIC LOCAL (BEST PRACTICE) ---\n";
    SingletonStaticLocal& s1 = SingletonStaticLocal::getInstance();
    SingletonStaticLocal& s2 = SingletonStaticLocal::getInstance();
    cout << (&s1 == &s2 ? "Same Instance\n" : "Different Instances\n");
    s1.doSomething();

    return 0;
}
/*
Which Singleton Should You Use in Real Projects?

| Pattern Type          | Recommended  |
| --------------------- | ------------ |
| Lazy (basic)          | ❌ Not safe   |
| Thread Safe (mutex)   | ✅ Acceptable |
| Eager                 | ⚠️ Rare use  |
| Double-Checked        | ⚠️ Advanced  |
| Static Local (C++11+) | ✅✅ BEST      |


✅ Interview Answer:

In modern C++, static local Singleton is best because it is thread-safe, simple, efficient, and avoids manual mutex handling.

 */