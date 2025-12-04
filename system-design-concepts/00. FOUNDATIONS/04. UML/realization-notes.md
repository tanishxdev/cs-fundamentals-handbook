#  What is Realization?
![Realization](https://media.geeksforgeeks.org/wp-content/uploads/20250829165046859312/realization.webp)

* **Definition**: Realization is a UML relationship where a **class implements an interface**.
* It represents an **“implements” relationship**, not **“is-a”** (like inheritance).
* The **interface** only declares behavior (methods), while the **class provides concrete implementation**.
* **UML Notation**:
  * **Dashed line** with **hollow triangle** from class → interface.

```
Person ---------▷ Owner
Corporation ----▷ Owner
```

---

# 🔑 Difference from Generalization

| Concept      | Generalization (Inheritance)           | Realization (Interface Implementation)                           |
| ------------ | -------------------------------------- | ---------------------------------------------------------------- |
| Relationship | “is-a”                                 | “implements”                                                     |
| Code         | Class inherits another class           | Class implements an interface (abstract class in C++)            |
| Method Body  | Parent may already have implementation | Interface never has implementation (only pure virtual functions) |
| UML          | Solid line with hollow triangle        | Dashed line with hollow triangle                                 |

---

# 📝 Example: Owner Interface

```cpp
#include <iostream>
#include <string>
using namespace std;

// 🎯 Interface (Abstract class with pure virtual functions)
class Owner {
public:
    virtual void acquire(const string& property) = 0;   // pure virtual
    virtual void dispose(const string& property) = 0;   // pure virtual
    virtual ~Owner() = default; // virtual destructor for safety
};

// 👤 Person realizes Owner
class Person : public Owner {
public:
    void acquire(const string& property) override {
        cout << "Person acquired " << property << endl;
    }
    void dispose(const string& property) override {
        cout << "Person disposed " << property << endl;
    }
};

// 🏢 Corporation realizes Owner
class Corporation : public Owner {
public:
    void acquire(const string& property) override {
        cout << "Corporation acquired " << property << endl;
    }
    void dispose(const string& property) override {
        cout << "Corporation disposed " << property << endl;
    }
};

int main() {
    // Polymorphism using Interface
    Owner* o1 = new Person();
    Owner* o2 = new Corporation();

    o1->acquire("House");
    o2->acquire("Office");

    o1->dispose("Car");
    o2->dispose("Company Vehicle");

    delete o1;
    delete o2;
    return 0;
}
```

---

### ✅ Output

```
Person acquired House
Corporation acquired Office
Person disposed Car
Corporation disposed Company Vehicle
```

---

# 🧠 Why Use Realization?

* Defines **contracts (what must be done)** without implementation.
* Allows multiple classes to **implement the same behavior differently**.
* Promotes **flexibility** → new classes can realize the same interface without changing old code.
* Supports **polymorphism** (we can treat all realizations as `Owner*`).

---

# 🔎 Real-World Analogies

* **Interface** = contract or rulebook.
* **Classes** = players who follow the rulebook in their own way.

Examples:

* `PaymentGateway` interface → `PayPal`, `Stripe`, `GooglePay` classes realize it.
* `Shape` interface → `Circle`, `Square`, `Triangle` realize it.

---

# 🎯 Quick Recap of Relationships

| Relationship       | Example                    | UML                          |
| ------------------ | -------------------------- | ---------------------------- |
| **Association**    | Teacher ↔ Student          | Solid line                   |
| **Aggregation**    | Library ▷ Book             | Hollow diamond               |
| **Composition**    | House ◆ Room               | Solid diamond                |
| **Generalization** | Dog → Animal               | Solid line, hollow triangle  |
| **Realization**    | Person → Owner (interface) | Dashed line, hollow triangle |
