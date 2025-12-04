#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

**Polymorphism** means “many forms” —  
it allows one interface (function or class) to behave differently based on input or context.

There are **two main types** of polymorphism in C++:

1. **Compile-Time Polymorphism (Static Binding)**
   - Decided at compile time.
   - Achieved through **function overloading** or **operator overloading**.

2. **Run-Time Polymorphism (Dynamic Binding)**
   - Decided at runtime.
   - Achieved through **virtual functions** and **function overriding**.

👉 Why Polymorphism is Needed

| Problem Without Polymorphism | Solution With Polymorphism |
| ----------------------------- | --------------------------- |
| Same operation name but for different types (int, double) → duplication. | Function overloading allows same function name with different parameter types. |
| Behavior differs based on object type but interface is same. | Virtual functions let derived classes override behavior dynamically. |

👉 Real-life Analogy

When you call “speak()”:
- A dog barks
- A cat meows  
Yet, the command (speak) is **same** — only the response differs.  
That’s **polymorphism** — one function name, many behaviors.

👉 Problem Statement

1. Demonstrate **Compile-Time Polymorphism** using Function Overloading.  
2. Demonstrate **Run-Time Polymorphism** using Virtual Functions and Function Overriding.  
3. Show how the same interface can behave differently based on the object type.
*/

/*
------------------------------------------------------------
Problem: Demonstrate Compile-Time & Run-Time Polymorphism
------------------------------------------------------------
Goal:
1. Show static binding (function overloading) in action.
2. Show dynamic binding (virtual functions) with base pointer.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// 1️⃣ COMPILE-TIME POLYMORPHISM (Function Overloading)
// ----------------------------------------------------------
class Math {
public:
    // same function name, different parameter types / counts
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }

    int add(int a, int b, int c) {
        return a + b + c;
    }

    double add(double a, double b, double c) {
        return a + b + c;
    }
};

// ----------------------------------------------------------
// 2️⃣ RUN-TIME POLYMORPHISM (Virtual Functions)
// ----------------------------------------------------------
class Animal {
public:
    // Virtual function — dynamically resolved at runtime
    virtual void sound() {
        cout << "Animal makes a sound" << endl;
    }

    // Virtual destructor (best practice for base classes)
    virtual ~Animal() {}
};

// Derived Class 1
class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks" << endl;
    }
};

// Derived Class 2
class Cat : public Animal {
public:
    void sound() override {
        cout << "Cat meows" << endl;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates both types of Polymorphism
// ----------------------------------------------------------
int main() {
    // 1️⃣ Compile-Time Polymorphism
    cout << "----- Compile-Time Polymorphism (Function Overloading) -----" << endl;
    Math mathObj;
    cout << "add(int, int): " << mathObj.add(10, 20) << endl;
    cout << "add(double, double): " << mathObj.add(10.5, 20.5) << endl;
    cout << "add(int, int, int): " << mathObj.add(10, 20, 30) << endl;
    cout << "add(double, double, double): " << mathObj.add(10.5, 20.5, 30.5) << endl;

    cout << "\n----- Run-Time Polymorphism (Virtual Functions) -----" << endl;

    // 2️⃣ Run-Time Polymorphism
    Animal* animal1 = new Dog();  // base pointer → derived object
    Animal* animal2 = new Cat();  // base pointer → derived object

    // Virtual call → resolved dynamically based on actual object
    animal1->sound(); // Dog barks
    animal2->sound(); // Cat meows

    // Free memory
    delete animal1;
    delete animal2;

    return 0;
}

/*
👉 Step-by-Step Flow

1. **Compile-Time Polymorphism**
   - The `add()` function has multiple versions.
   - Compiler decides which one to call based on parameter types/counts.
   - Happens during compilation (static binding).

2. **Run-Time Polymorphism**
   - The `sound()` function is declared as virtual in base class `Animal`.
   - Derived classes override it (`Dog`, `Cat`).
   - The decision of which function to call happens *at runtime* (dynamic binding).

👉 Example Output

----- Compile-Time Polymorphism (Function Overloading) -----
add(int, int): 30
add(double, double): 31
add(int, int, int): 60
add(double, double, double): 61.5

----- Run-Time Polymorphism (Virtual Functions) -----
Dog barks
Cat meows

👉 Key Takeaways

| Concept | Description |
| -------- | ------------ |
| **Polymorphism** | One interface, multiple behaviors. |
| **Compile-Time (Static Binding)** | Function is selected at compile time (via overloading). |
| **Run-Time (Dynamic Binding)** | Function resolved at runtime (via overriding and virtual keyword). |
| **Virtual Function** | Enables runtime polymorphism — ensures the correct derived function is called. |
| **Base Pointer / Derived Object** | Allows calling overridden functions using a common interface. |

👉 How Polymorphism Helps in System Design

In large-scale architectures:
- It enables **plug-and-play components**.
- The **core system interacts via interfaces**, not concrete classes.
- Each subclass defines its own behavior, promoting flexibility and scalability.

**Example (System Design Analogy):**
- Abstract Class: `NotificationService`
  - Function: `sendNotification()`
- Derived: `EmailNotification`, `SMSNotification`, `PushNotification`
- Business code calls only:
  ```cpp
  NotificationService* service = new EmailNotification();
  service->sendNotification();
→ Same interface, different implementations depending on runtime context.

👉 Final Recap of OOP Pillars
| Pillar            | Description                                 |
| ----------------- | ------------------------------------------- |
| **Encapsulation** | Hide data and provide controlled access.    |
| **Abstraction**   | Hide complexity, show essential features.   |
| **Inheritance**   | Reuse and extend functionality.             |
| **Polymorphism**  | Same interface, multiple forms of behavior. |

*/