# 🧠 Adapter Design Pattern (C++ Full Example + Explanation)

---

## 🔍 Concept

The **Adapter Design Pattern** allows **two incompatible interfaces** to work together.
It **acts as a bridge** between old code (`Adaptee`) and new code (`Target`).

Think of it like:

> You have a laptop with a **USB-C port**, but your pen drive uses **USB-A** —
> You use a **USB adapter** to make them work together.

---

## 💡 Why Use Adapter?

When:

* You have **legacy code** (old system) that doesn’t match new requirements.
* You need to **reuse existing code** without modifying it.
* You want to **connect incompatible systems** safely.

---

## 🏗️ Components

| Component            | Role                                                     |
| -------------------- | -------------------------------------------------------- |
| **Target Interface** | Defines what the client expects (the new interface).     |
| **Adaptee**          | Existing class with incompatible interface (old code).   |
| **Adapter**          | Connects Adaptee to Target by converting calls.          |
| **Client**           | Uses the Target interface without knowing about Adaptee. |

---

## 🧩 Example Scenario

You have an **old printing system** (`LegacyPrinter`) with a method `printDocument()`.
Your new application expects a class with a `print()` function.
You cannot modify `LegacyPrinter` (it’s part of an old library),
so you use an **Adapter** to bridge the gap.

---

## 🧱 Implementation (C++)

```cpp
#include <iostream>
using namespace std;

// --- 1️⃣ Target Interface ---
class Printer {
public:
    virtual void print() = 0;  // Expected by the new system
    virtual ~Printer() {}
};

// --- 2️⃣ Adaptee (Legacy System) ---
class LegacyPrinter {
public:
    void printDocument() {  // Old incompatible method
        cout << "🖨️ Legacy Printer is printing a document..." << endl;
    }
};

// --- 3️⃣ Adapter ---
class PrinterAdapter : public Printer {
private:
    LegacyPrinter* legacyPrinter;  // Composition (has-a relationship)
public:
    PrinterAdapter(LegacyPrinter* lp) : legacyPrinter(lp) {}

    void print() override {  // Adapts new method to old one
        legacyPrinter->printDocument();
    }
};

// --- 4️⃣ Client ---
int main() {
    LegacyPrinter* oldPrinter = new LegacyPrinter();

    // Adapter allows the new system to use old printer
    Printer* printer = new PrinterAdapter(oldPrinter);

    cout << "🧩 Using Adapter Pattern:" << endl;
    printer->print();

    // Cleanup
    delete oldPrinter;
    delete printer;
    return 0;
}
```

---

## 🧠 Step-by-Step Thinking

### 1️⃣ Problem:

New software expects a `print()` function,
but the old library has `printDocument()`.

Directly using the old library breaks interface compatibility.

### 2️⃣ Solution:

Create an **Adapter (`PrinterAdapter`)** that:

* Implements the new interface `Printer`.
* Internally calls the old method `printDocument()`.

### 3️⃣ Benefit:

Now, the **Client** can call `print()` without caring whether it’s a `LegacyPrinter` or a new printer.

---

## ⚙️ Output

```
🧩 Using Adapter Pattern:
🖨️ Legacy Printer is printing a document...
```

---

## ✅ Advantages

1. **Reusability:** Use legacy or third-party code without modification.
2. **Flexibility:** Change implementation without touching client code.
3. **Loose Coupling:** Client is independent of implementation details.
4. **Integration:** Useful when merging systems or migrating APIs.

---

## ❌ Disadvantages

1. Adds **extra layer** — minor performance overhead.
2. Makes design **slightly more complex**.
3. **Overuse** can clutter code if too many adapters are introduced.

---

## 💬 Real-Life Analogies

| Real-Life Example         | Description                                                 |
| ------------------------- | ----------------------------------------------------------- |
| **Mobile charger**        | Converts voltage from wall socket to what your phone needs. |
| **Language translator**   | Converts English → Hindi so both people can talk.           |
| **HDMI to VGA converter** | Connects modern laptops to old projectors.                  |

---

## 🧩 When to Use

* Integrating **old APIs** into new systems.
* Bridging **different data formats** (e.g., JSON ↔ XML).
* Making **third-party libraries** compatible.
* While **refactoring code** to avoid breaking changes.

---

## 🚫 When Not to Use

* When **interfaces are already compatible**.
* When you can **refactor old code directly**.
* For **simple changes** where adapter adds unnecessary complexity.

---

## 🧠 Key Takeaway

> Adapter = **Connector between incompatible interfaces**
> It allows **new system + old system** to work **seamlessly**
> without **modifying either**.

---