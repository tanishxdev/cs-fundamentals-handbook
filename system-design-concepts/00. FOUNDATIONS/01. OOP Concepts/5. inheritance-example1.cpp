#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

**Inheritance** allows one class (child/derived) to **reuse properties and behaviors**
of another class (parent/base).  
It helps in **code reusability, logical hierarchy**, and **extensibility**.

In simple words:
> “A child class inherits features of its parent class.”

👉 Why Inheritance is Needed

| Without Inheritance | With Inheritance |
| -------------------- | ---------------- |
| Duplicate code in every class (eat(), sleep(), etc.) | Reuse code from base class — no duplication |
| Difficult to maintain — changes must be made everywhere | Maintain in one place — automatically inherited |
| No clear hierarchy | Logical relationship — promotes modular design |

👉 Real-life Analogy

Think of a **family tree**:
- “Animal” is a generic parent.
- “Dog”, “Cat”, “Bird” inherit traits like eating and sleeping but add their own behaviors.

👉 Problem Statement

Design a system to demonstrate how a derived class (Dog) can inherit
common behaviors (like eat() and sleep()) from a base class (Animal),
and add its own unique behavior (bark()).
*/

/*
------------------------------------------------------------
Problem: Demonstrate Inheritance using Animal-Dog Example
------------------------------------------------------------
Goal:
1. Base class 'Animal' defines common functions.
2. Derived class 'Dog' inherits those features and adds specific behavior.
3. Demonstrate code reusability and hierarchy.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// BASE CLASS: Animal
// Defines general behavior common to all animals
// ----------------------------------------------------------
class Animal {
public:
    void eat() {
        cout << "Animal is eating..." << endl;
    }

    void sleep() {
        cout << "Animal is sleeping..." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Dog
// Inherits from Animal and adds its own behavior
// ----------------------------------------------------------
class Dog : public Animal {
public:
    void bark() {
        cout << "Dog is barking..." << endl;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates Inheritance
// ----------------------------------------------------------
int main() {
    Dog myDog;   // Derived class object

    // Inherited methods from Animal class
    myDog.eat();     // Reused from base
    myDog.sleep();   // Reused from base

    // Child class-specific method
    myDog.bark();    // Unique to Dog class

    return 0;
}

/*
👉 Step-by-Step Flow

1. The base class `Animal` provides generic behavior (`eat()`, `sleep()`).
2. The derived class `Dog` inherits those methods automatically.
3. The derived class also adds a new function `bark()`.
4. When we create a Dog object:
    - It can use both `Animal`'s functions (eat, sleep)
    - And its own (bark)

👉 Example Output

Animal is eating...
Animal is sleeping...
Dog is barking...

👉 Key Takeaways

| Concept                       | Description |
| --------                      | ------------ |
| **Base Class (Parent)**    | Defines general/shared behaviors. |
| **Derived Class (Child)** | Inherits base class behaviors, adds specific ones. |
| **Code Reusability**      | Avoids duplication by reusing base logic. |
| **Hierarchy**             | Models “is-a” relationship (Dog *is an* Animal). |

👉 How Inheritance Helps in System Design

In large-scale architectures:
- You define **base classes or interfaces** for common operations.
- Derived classes implement or extend those behaviors for specific entities.

**Example:**
- Base class: `NotificationService`
  - Methods: `sendNotification()`
- Derived classes: `EmailService`, `SMSService`, `PushService`
  - Each implements sending differently but reuses shared logic.

**Result:**  
- Centralized logic, easier maintenance, and scalability.

👉 Next Steps

We’ve now learned:
1. **Encapsulation** — Data protection  
2. **Abstraction** — Hiding complexity  
3. **Inheritance** — Reusing and extending behavior  

Next concept will be **Polymorphism**, where the same function behaves differently based on the object type.
*/
