#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

- Abstraction means hiding complex implementation details and showing only the essential functionalities to the user.

In other words:

- “Tell what to do, not how to do it.”
- The main purpose of abstraction is to reduce complexity, increase modularity, and separate interface from implementation.

👉 Why Abstraction is Needed

| Without Abstraction                                           | With Abstraction                                             |
| ------------------------------------------------------------- | ------------------------------------------------------------ |
| The user must understand the internal working of every class. | The user only interacts through a well-defined interface.    |
| High coupling between modules.                                | Loose coupling — only contract (interface) matters.          |
| Difficult to modify or extend.                                | Easy to add new classes that follow the same abstract rules. |

👉 Real-life Analogy

When you drive a car, you use:
- Accelerate pedal
- Brake pedal
- Ignition button

You don’t need to know how the fuel injects or engine combustion works.
That’s abstraction — you interact through a simplified interface, while the implementation stays hidden.

👉 Problem Statement

Design a system where different types of vehicles (Car, Bike, etc.) can perform basic actions like accelerate() and brake() without exposing their internal implementation.
Use abstract classes (interfaces) and pure virtual functions to achieve abstraction.

 */

/*
------------------------------------------------------------
Problem: Demonstrate Abstraction using Abstract Class
------------------------------------------------------------
Goal:
1. Define a base class 'Vehicle' that only specifies the interface.
2. Derived classes (like Car) implement those functions.
3. The user interacts through a base class pointer, without knowing
   the internal details of the derived class.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// ABSTRACT CLASS: Vehicle
// Contains pure virtual functions (no definition here)
// ----------------------------------------------------------
class Vehicle {
public:
    // Pure virtual functions — define "what" must be done
    virtual void accelerate() = 0; // Must be implemented by derived class
    virtual void brake() = 0;      // Must be implemented by derived class

    // Concrete (normal) function — common for all derived classes
    void startEngine() {
        cout << "Engine started!" << endl;
    }

    // Virtual destructor (good practice for base classes)
    virtual ~Vehicle() {}
};

// ----------------------------------------------------------
// DERIVED CLASS: Car
// Implements the abstract interface of Vehicle
// ----------------------------------------------------------
class Car : public Vehicle {
public:
    // Override pure virtual methods (implement how behavior works)
    void accelerate() override {
        cout << "Car accelerating..." << endl;
    }

    void brake() override {
        cout << "Car braking..." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Bike
// Another derived type implementing the same interface
// ----------------------------------------------------------
class Bike : public Vehicle {
public:
    void accelerate() override {
        cout << "Bike accelerating..." << endl;
    }

    void brake() override {
        cout << "Bike braking..." << endl;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates Abstraction
// ----------------------------------------------------------
int main() {
    // Vehicle v; ❌ Not allowed: cannot instantiate abstract class

    // ✅ Base class pointer holding derived object
    Vehicle* v1 = new Car();
    v1->startEngine();     // Common functionality
    v1->accelerate();      // Car-specific behavior
    v1->brake();           // Car-specific behavior
    delete v1;

    cout << "------------------\n";

    Vehicle* v2 = new Bike();
    v2->startEngine();
    v2->accelerate();
    v2->brake();
    delete v2;

    return 0;
}

/*
👉 Step-by-Step Flow

- Vehicle defines an interface (the blueprint) for any vehicle.
- Car and Bike implement the behavior (accelerate() and brake()).
- main() only talks to a Vehicle pointer — not caring which vehicle type it is.
→ This means we can add more vehicles (Truck, Bus) without changing main logic.


👉 Key Takeaways

| Concept                            | Description                                                            |
| ---------------------------------- | ---------------------------------------------------------------------- |
| **Abstract Class**                 | Cannot be instantiated; acts as a blueprint for derived classes.       |
| **Pure Virtual Function**          | Declared with `= 0`, must be implemented in derived class.             |
| **Virtual Destructor**             | Ensures derived destructors are called properly during cleanup.        |
| **Polymorphic Pointer (Vehicle*)** | Enables abstraction — you don’t care which derived class it points to. |

👉 How Abstraction Helps in System Design

In large-scale systems, abstraction helps separate:
- Interfaces (contracts) → what each module exposes
- Implementations (details) → how it internally works

Example:
- Payment System Interface → processPayment()
- Implementations: CreditCardPayment, PayPalPayment, UPIPayment

Frontend / main program interacts only with the abstract interface.
This makes the system extensible and maintainable — a core principle of scalable architecture.

*/