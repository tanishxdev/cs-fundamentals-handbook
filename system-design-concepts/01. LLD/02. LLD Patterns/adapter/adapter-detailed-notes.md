# **Adapter Design Pattern (C++ Implementation)**

---

### 1. Real-World Thinking

#### Problem Scenario

In large software systems, different modules often evolve separately — sometimes using incompatible interfaces. For instance, an old graphics rendering system might have a class `OldRenderer` with a method `drawShape()`, while your new system expects a `Renderer` interface with a method `render()`.

Modifying the old system can be risky, expensive, or even impossible (e.g., third-party library).
The **Adapter Pattern** helps by introducing a bridge — an intermediary class that translates between the two interfaces, enabling them to work together seamlessly.

#### Real-World Analogy

Think of a **mobile charger adapter**.
Your phone might need a USB-C connector, but the power socket provides a different plug or voltage. The adapter converts one form into another without changing either device.
Similarly, the software adapter converts one class interface into another expected by the client.

---

### 2. What is the Adapter Design Pattern

The **Adapter Design Pattern** is a **Structural Design Pattern** that allows objects with incompatible interfaces to collaborate.
It converts the interface of an existing class into another interface that the client expects.

**Intent:**

> Allow the interface of an existing class to be used as another interface. It enables classes with incompatible interfaces to work together.

---

### 3. Key Components

| **Component**        | **Role / Description**                                                                        |
| -------------------- | --------------------------------------------------------------------------------------------- |
| **Target Interface** | Defines the interface that the client expects to use.                                         |
| **Adaptee**          | The existing class that has a useful behavior but incompatible interface.                     |
| **Adapter**          | Implements the target interface and internally calls the adaptee’s methods.                   |
| **Client**           | Works only with the target interface and remains unaware of the adaptee’s internal structure. |

---

### 4. How It Solves Problems

| **Problem Without Pattern**                                         | **Solution With Adapter Pattern**                                  |
| ------------------------------------------------------------------- | ------------------------------------------------------------------ |
| Existing code cannot be modified to fit new interface requirements. | Adapter bridges the two interfaces without altering existing code. |
| Direct modification may introduce bugs or break compatibility.      | Adapter isolates the changes, preserving original code safety.     |
| Integration between legacy and modern systems is difficult.         | Adapter standardizes communication between incompatible modules.   |

---

### 5. Real-World Analogies

1. **Power Plug Adapter:** Converts one plug type to another so devices can function in different countries.
2. **Database Connector:** Translates between different query formats (e.g., MySQL vs PostgreSQL drivers).
3. **USB-to-Ethernet Adapter:** Allows a USB port to communicate with Ethernet — bridging two incompatible systems.

---

### 6. Implementation (C++ Example)

![](https://media.geeksforgeeks.org/wp-content/uploads/20250905161148734950/Adapter-Design-Pattern.webp)

![](https://media.geeksforgeeks.org/wp-content/uploads/20240204210126/Class-Diagram-of-Adapter-Design-Pattern_.webp)
#### Step 1: Target Interface

Defines the operation that the client expects (`print()`).

```cpp
#include <bits/stdc++.h>
using namespace std;

// Target Interface
class Printer {
public:
    virtual void print() = 0;
    virtual ~Printer() = default;
};
```

#### Step 2: Adaptee

Represents an existing system or legacy class with an incompatible method name.

```cpp
// Adaptee
class LegacyPrinter {
public:
    void printDocument() {
        cout << "Legacy Printer is printing a document." << endl;
    }
};
```

#### Step 3: Adapter

Bridges the gap by implementing the `Printer` interface while internally using `LegacyPrinter`.

```cpp
// Adapter
class PrinterAdapter : public Printer {
private:
    LegacyPrinter* legacyPrinter;

public:
    PrinterAdapter(LegacyPrinter* lp) : legacyPrinter(lp) {}

    void print() override {
        legacyPrinter->printDocument();
    }
};
```

#### Step 4: Client Code

Uses only the `Printer` interface. The adapter handles compatibility internally.

```cpp
// Client
int main() {
    LegacyPrinter* oldPrinter = new LegacyPrinter();
    Printer* adapter = new PrinterAdapter(oldPrinter);

    adapter->print();  // The client calls print(), unaware of LegacyPrinter details.

    delete adapter;
    delete oldPrinter;
    return 0;
}
```

#### **Output**

```
Legacy Printer is printing a document.
```
---

### **Code Explanation**

#### **Concept Recap**

* **Intent:**
  The Adapter Pattern allows **two incompatible interfaces** to work together.
  It **converts** the interface of one class (the *Adaptee*) into another interface (the *Target*) that clients expect.

---

#### **Step 1: Target Interface**

```cpp
class Printer {
public:
    virtual void print() = 0;
    virtual ~Printer() = default;
};
```

##### **What this does:**

* Defines a **standard interface (`Printer`)** that clients will use.
* The `print()` method is **pure virtual**, meaning every concrete class must implement it.
* The **client** only knows about `Printer`, not any specific implementation.
* `virtual ~Printer() = default;` ensures proper cleanup for derived classes.

##### **Why we need this:**

* It represents the **expected behavior** from the client’s perspective — in this case, the ability to `print()`.
* Any class that wants to act like a `Printer` must follow this interface.

---

#### **Step 2: Adaptee (Legacy System)**

```cpp
class LegacyPrinter {
public:
    void printDocument() {
        cout << "Legacy Printer is printing a document." << endl;
    }
};
```

##### **What this does:**

* Represents an **existing or old system** with an **incompatible interface**.
* It has a method named `printDocument()`, not `print()`, so the client can’t use it directly.

##### **Why we need this:**

* In real-world scenarios, we often have **existing systems** that can’t be modified (e.g., third-party libraries or legacy code).
* Instead of rewriting them, we use an **adapter** to make them compatible.

---

#### **Step 3: Adapter**

```cpp
class PrinterAdapter : public Printer {
private:
    LegacyPrinter* legacyPrinter;

public:
    PrinterAdapter(LegacyPrinter* lp) : legacyPrinter(lp) {}

    void print() override {
        legacyPrinter->printDocument();
    }
};
```

##### **What this does:**

* Implements the **Target Interface (`Printer`)**, so it can be used by the client.
* Holds a **reference to the Adaptee (`LegacyPrinter`)**.
* The `print()` function (expected by the client) internally calls `printDocument()` (Adaptee’s method).

#### **Why we need this:**
#
* It **“adapts”** one interface (`printDocument()`) to another (`print()`).
* The client can now interact with the `LegacyPrinter` without changing its code.

##### **Key idea:**

> Adapter = Translator between the client and legacy code.

---

#### **Step 4: Client Code**

```cpp
int main() {
    LegacyPrinter* oldPrinter = new LegacyPrinter();
    Printer* adapter = new PrinterAdapter(oldPrinter);

    adapter->print();  // The client calls print(), unaware of LegacyPrinter details.

    delete adapter;
    delete oldPrinter;
    return 0;
}
```

##### **What happens here:**

1. The client creates a `LegacyPrinter` (incompatible class).
2. Then wraps it with a `PrinterAdapter`.
3. Calls `adapter->print()` — which the adapter internally forwards to `oldPrinter->printDocument()`.

###### **Output:**

```
Legacy Printer is printing a document.
```

###### **Why this works beautifully:**

* The client code **only depends on the `Printer` interface** — it’s **decoupled** from the legacy class.
* The **adapter hides complexity** and handles compatibility.

---

##### **Flow Summary**

| Role             | Class            | Responsibility                                                     |
| ---------------- | ---------------- | ------------------------------------------------------------------ |
| Target Interface | `Printer`        | Defines the expected interface (`print()`)                         |
| Adaptee          | `LegacyPrinter`  | Has incompatible method (`printDocument()`)                        |
| Adapter          | `PrinterAdapter` | Bridges gap between `Printer` and `LegacyPrinter`                  |
| Client           | `main()`         | Uses `Printer` interface without caring about compatibility issues |

---

#### **Key Takeaways**

* The Adapter Pattern is all about **interface conversion**.
* It promotes **code reusability** — you can reuse legacy or third-party classes without modifying them.
* The client remains **agnostic** to underlying implementations.
* Common analogy: **A power plug adapter** that lets a 3-pin plug fit into a 2-pin socket.


---

### 7. Advantages

* Promotes **code reuse** without altering existing classes.
* Enables **interoperability** between incompatible systems.
* Decouples client code from specific implementations.
* Simplifies integration of legacy or third-party modules.
* Makes systems more **flexible and maintainable**.

---

### 8. Disadvantages

* Adds an extra **layer of abstraction** and complexity.
* Can cause **slight performance overhead** due to indirection.
* Overuse may clutter design with too many adapter classes.
* May require multiple adapters if many interfaces differ.

---

### 9. When to Use

* When you need to **reuse existing code** with incompatible interfaces.
* When **integrating old systems** into modern applications.
* When a **third-party library** cannot be modified but needs adaptation.
* When standardizing interfaces across different modules or APIs.

---

### 10. When Not to Use

* When all classes already share a compatible interface.
* When it’s simpler to **refactor existing code** rather than adapt it.
* In **small or short-lived projects** where abstraction adds unnecessary complexity.
* In **performance-critical** systems where adapter overhead matters.

---

### ✅ Key Takeaways

1. **Purpose:** To make incompatible interfaces work together without changing existing code.
2. **Type:** Structural pattern – focuses on class and object composition.
3. **Core Idea:** Acts as a translator between old and new interfaces.
4. **Common Forms:**

   * **Class Adapter** (uses inheritance)
   * **Object Adapter** (uses composition – most common)
5. **Best Use:** Integrating legacy or third-party code into modern systems.
6. **Caution:** Avoid unnecessary use where direct integration or refactoring is simpler.

---