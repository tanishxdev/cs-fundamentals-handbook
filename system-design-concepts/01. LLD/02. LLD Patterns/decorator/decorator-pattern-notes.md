# **Decorator Design Pattern (C++ Implementation)**

---

### 1. Real-World Thinking

#### Problem Scenario

Suppose you are building a **coffee shop application**. You have different types of coffee like `Espresso` or `Latte`. Customers can add optional toppings like **milk**, **sugar**, or **whipped cream**.

**Challenge:**

* You could create a separate class for every possible combination (`EspressoWithMilk`, `LatteWithSugar`, etc.).
* This approach is **rigid**, not scalable, and violates the **Open/Closed Principle**.

**Solution:**

* Use the **Decorator Pattern**, which allows you to **dynamically add behaviors** (toppings) to objects without modifying existing classes.

#### Real-World Analogy

![](https://media.geeksforgeeks.org/wp-content/uploads/20250905170841269678/Decorator-Design-Pattern.webp)

Think of a **customizable pizza**:

* Base pizza = `PlainPizza`
* Toppings = `Cheese`, `Tomato`, `Capsicum`
* Each topping **wraps the pizza** and adds cost/behavior without modifying the base pizza.

---

### 2. What is the Decorator Design Pattern

The **Decorator Design Pattern** is a **Structural Pattern** that lets you **dynamically add behavior** to objects at runtime.

**Intent:**

> Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.

---

### 3. Key Components

| **Component**           | **Role / Description**                                                                          |
| ----------------------- | ----------------------------------------------------------------------------------------------- |
| **Component Interface** | Defines the standard interface (`getDescription()` and `getCost()`) for objects and decorators. |
| **Concrete Component**  | The base object with core functionality (e.g., `PlainCoffee`).                                  |
| **Decorator**           | Abstract class that holds a reference to a Component and delegates calls.                       |
| **Concrete Decorator**  | Adds new functionality by extending the Decorator (e.g., `MilkDecorator`).                      |
| **Client**              | Uses components via the Component interface without knowing the concrete class details.         |

---

### 4. How It Solves Problems

| **Problem Without Pattern**                                                   | **Solution With Decorator Pattern**                                                 |
| ----------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| Need multiple combinations of base objects + features → rigid class explosion | Decorator adds features **dynamically** using composition, avoiding class explosion |
| Changing existing classes risks breaking code                                 | Decorators **wrap existing objects** without modifying them                         |
| Hard to extend functionality in runtime                                       | You can **add/remove responsibilities dynamically** at runtime                      |

---

### 5. Real-World Examples

1. **Coffee Shop Application:** Add milk, sugar, whipped cream dynamically to coffee.
2. **Pizza Customization:** Wrap a base pizza with multiple toppings.
3. **Text Processing:** Apply `Bold`, `Italic`, or `Underline` dynamically to text objects.
4. **Java I/O Streams:** Wrap `FileInputStream` with `BufferedInputStream` or `DataInputStream` to add functionality.

---

### 6. C++ Implementation Example

![](https://media.geeksforgeeks.org/wp-content/uploads/20240405114106/Decoratorpatternclassdiagram.jpg)
#### Step 1: Component Interface

```cpp
#include <bits/stdc++.h>
using namespace std;

// Component Interface
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~Coffee() = default;
};
```

* Defines a standard interface for **core objects and decorators**.
* Clients interact only with this interface.

---

#### Step 2: Concrete Component

```cpp
class PlainCoffee : public Coffee {
public:
    string getDescription() override {
        return "Plain Coffee";
    }
    double getCost() override {
        return 2.0;
    }
};
```

* Represents the **base object** with default behavior.
* Implements the `Coffee` interface.

---

#### Step 3: Decorator

```cpp
class CoffeeDecorator : public Coffee {
protected:
    Coffee* decoratedCoffee;  // reference to the object being decorated
public:
    CoffeeDecorator(Coffee* coffee) : decoratedCoffee(coffee) {}
    string getDescription() override {
        return decoratedCoffee->getDescription();
    }
    double getCost() override {
        return decoratedCoffee->getCost();
    }
};
```

* Abstract decorator holds a **reference** to a `Coffee` object.
* Delegates `getDescription()` and `getCost()` calls to the decorated object.

---

#### Step 4: Concrete Decorators

```cpp
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
    string getDescription() override {
        return decoratedCoffee->getDescription() + ", Milk";
    }
    double getCost() override {
        return decoratedCoffee->getCost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}
    string getDescription() override {
        return decoratedCoffee->getDescription() + ", Sugar";
    }
    double getCost() override {
        return decoratedCoffee->getCost() + 0.2;
    }
};
```

* Each concrete decorator **extends functionality** of the base object.
* Can **stack multiple decorators** dynamically.

---

#### Step 5: Client Code

```cpp
int main() {
    Coffee* coffee = new PlainCoffee();
    cout << coffee->getDescription() << " - $" << coffee->getCost() << endl;

    Coffee* milkCoffee = new MilkDecorator(new PlainCoffee());
    cout << milkCoffee->getDescription() << " - $" << milkCoffee->getCost() << endl;

    Coffee* sugarMilkCoffee = new SugarDecorator(new MilkDecorator(new PlainCoffee()));
    cout << sugarMilkCoffee->getDescription() << " - $" << sugarMilkCoffee->getCost() << endl;

    delete coffee;
    delete milkCoffee;
    delete sugarMilkCoffee;
    return 0;
}
```

**Output:**

```
Plain Coffee - $2
Plain Coffee, Milk - $2.5
Plain Coffee, Milk, Sugar - $2.7
```

---

### 7. Code Explanation

**Flow Summary:**

| Role                | Class                             | Responsibility                |
| ------------------- | --------------------------------- | ----------------------------- |
| Component Interface | `Coffee`                          | Defines the common methods    |
| Concrete Component  | `PlainCoffee`                     | Base object implementation    |
| Decorator           | `CoffeeDecorator`                 | Holds reference and delegates |
| Concrete Decorators | `MilkDecorator`, `SugarDecorator` | Add behavior and cost         |
| Client              | `main()`                          | Uses component via interface  |

**Key Concept:**

> Decorator **wraps** an object and **adds functionality dynamically** without altering the base object.

---

### 8. Advantages

* Supports **Open/Closed Principle**.
* Dynamically **add/remove responsibilities** at runtime.
* **Flexible stacking** of multiple decorators.
* Avoids **class explosion** for every combination of features.
* **Reusability:** Same decorators can be applied to multiple objects.

---

### 9. Disadvantages

* Can make code **complex** with many layers of decorators.
* Harder to **debug** due to many wrapping layers.
* Slight **performance overhead** due to multiple delegation calls.

---

### 10. When to Use

* When you need **dynamic behavior addition** without modifying existing classes.
* When subclassing leads to **class explosion**.
* When working with **third-party libraries** where source code cannot be changed.
* For **layering behaviors** in text formatting, streaming, or UI components.

---

### ✅ Key Takeaways

1. **Purpose:** Dynamically add behavior to objects at runtime.
2. **Type:** Structural Pattern.
3. **Core Idea:** Wrap objects with decorators instead of modifying them.
4. **Composition over Inheritance:** Promotes flexible extension.
5. **Best Use:** Coffee shop customizations, pizza toppings, UI decorations, I/O stream enhancements.
6. **Caution:** Avoid excessive layers of decorators to maintain readability.

---
