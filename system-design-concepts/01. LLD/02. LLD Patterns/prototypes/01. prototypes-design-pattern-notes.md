# **Prototype Design Pattern**

## **1. Intuition — Why This Pattern Exists**

### Problem Scenario:

Imagine you are building:

* A **graphics editor** (like Figma, Photoshop, or MS Paint).
* It has shapes (Circle, Rectangle, Polygon, etc.) with styles, colors, borders, gradients, shadows, etc.

Now suppose:

* Creating a new shape means setting **all properties manually** every time.
* That’s **time-consuming** and **error-prone**.
* You often want **similar shapes** with small changes (e.g., a red circle → a blue circle).

Instead of rebuilding the entire shape again from scratch,
you could simply **copy an existing shape** and **modify it slightly**.

That’s the **Prototype Design Pattern** in action.

---

## **2. What is Prototype Design Pattern**

* The **Prototype Pattern** is a **creational design pattern**.
* It lets you **clone existing objects** instead of creating new ones from scratch.
* This is helpful when:

  * Object creation is **expensive** (e.g., resource-heavy initialization).
  * You need **many similar objects** with small variations.

---

## **3. Real-Life Analogies**

| Real-World Analogy     | Explanation                                                                                              |
| ---------------------- | -------------------------------------------------------------------------------------------------------- |
| **Document Templates** | You clone a base document (like a resume or report) and modify content — instead of designing from zero. |
| **Game Engines**       | You clone enemies, terrains, or characters with similar stats — avoids re-initializing complex models.   |
| **UI Components**      | Clone a pre-styled button or card and just tweak colors or labels.                                       |

---

## **4. Structure (Core Components)**

| Component               | Role                                                                            |
| ----------------------- | ------------------------------------------------------------------------------- |
| **Prototype Interface** | Declares the `clone()` method — defines how objects are copied.                 |
| **Concrete Prototype**  | Implements the clone logic for a specific class.                                |
| **Client**              | Requests new objects by cloning existing ones instead of creating from scratch. |

---

## **5. UML Flow (In Simple Words)**

![](https://media.geeksforgeeks.org/wp-content/uploads/20240202092603/PrototypeComponentdrawio-(2).png)
```
Client ---> Prototype (interface)
           /          \
ConcretePrototype1   ConcretePrototype2
        ↑                      ↑
      clone()                clone()
```

Client asks for a copy of an existing prototype using the `clone()` method.

---

## **6. Example — Shape Cloning (JS Version)**

We’ll simulate a **drawing app** where shapes (like circles) can be cloned efficiently.

---

### Step 1: Prototype Interface

```javascript
class Shape {
    clone() {
        throw new Error("Method not implemented.");
    }
    draw() {
        throw new Error("Method not implemented.");
    }
}
```

* `Shape` defines the **interface** every shape must follow.
* Each shape can **clone itself** and **draw itself**.

---

### Step 2: Concrete Prototype

```javascript
class Circle extends Shape {
    constructor(color) {
        super();
        this.color = color;
    }

    clone() {
        // Creates a new circle with the same color
        return new Circle(this.color);
    }

    draw() {
        console.log(`🎨 Drawing a ${this.color} circle.`);
    }
}
```

* `clone()` → returns a **new Circle object** with the same color.
* `draw()` → displays how the circle looks.

---

### Step 3: Client Code

```javascript
class ShapeClient {
    constructor(shapePrototype) {
        this.shapePrototype = shapePrototype;
    }

    createShape() {
        return this.shapePrototype.clone();
    }
}
```

* The **client** receives a prototype (like a red circle).
* It **creates new shapes** by calling `clone()` on it.

---

### Step 4: Main Program

```javascript
(() => {
    const circlePrototype = new Circle("red");  // Base prototype

    const client = new ShapeClient(circlePrototype);

    const redCircle = client.createShape();      // Cloning!
    redCircle.draw();                            // Output: 🎨 Drawing a red circle.
})();
```

**Output:**

```
Drawing a red circle.
```

---

## **7. What’s Really Happening Behind the Scenes**

| Step | Explanation                                                           |
| ---- | --------------------------------------------------------------------- |
| 1️⃣  | You have one “master copy” (prototype).                               |
| 2️⃣  | Instead of calling `new Circle()`, the client calls `clone()`.        |
| 3️⃣  | The prototype duplicates itself and returns a new instance.           |
| 4️⃣  | You can modify the clone’s properties if needed (e.g., change color). |

This pattern ensures:

* No need to re-initialize the object from scratch.
* Fast duplication with consistent behavior.

---

## **8. Shallow vs Deep Copy (Important!)**

| Type             | Description                                                    | Example                                     |
| ---------------- | -------------------------------------------------------------- | ------------------------------------------- |
| **Shallow Copy** | Copies only top-level fields. Nested objects are still shared. | `Object.assign({}, obj)`                    |
| **Deep Copy**    | Fully duplicates everything, including nested objects.         | `structuredClone(obj)` or manual deep clone |

**Prototype pattern** can use either — depends on your design.

---

## 💡 **9. When to Use Prototype Pattern**

Use it when:

* Object creation is **costly or complex**.
* You need **many similar objects**.
* You want to **reduce initialization overhead**.
* You need **runtime flexibility** (create objects dynamically).

---

## **10. When *Not* to Use It**

❌ Avoid it when:

* Objects are **simple** and cheap to create.
* Each object is **unique** and not reusable.
* Your system doesn’t require **runtime cloning**.
* You can easily use other patterns like **Factory** instead.

---

## ⚖️ **11. Advantages & Disadvantages**

### Advantages:

* Fast object creation (less CPU & memory).
* Reduces code duplication.
* Easy to create variations dynamically.
* Promotes **flexibility** and **runtime configuration**.

### Disadvantages:

* Complex cloning logic (especially for deep copies).
* Circular references or nested structures can cause issues.
* Maintaining clone behavior across subclasses is tricky.
* May hide dependencies if not documented well.

---

## **12. Real-World Example (C++ Version)**

Let’s now implement this pattern in **C++**, closer to how you’d use it in game or graphics engines.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Prototype Interface
class Shape {
public:
    virtual Shape* clone() = 0;
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// Concrete Prototype
class Circle : public Shape {
    string color;
public:
    Circle(string c) : color(c) {}
    Circle* clone() override {
        return new Circle(*this); // Copy constructor
    }
    void draw() override {
        cout << "🎨 Drawing a " << color << " circle.\n";
    }
};

// Client Code
int main() {
    Circle* redCircle = new Circle("red");   // Original prototype
    Circle* blueCircle = redCircle->clone(); // Clone it

    blueCircle->draw(); // Output: 🎨 Drawing a red circle.

    delete redCircle;
    delete blueCircle;
    return 0;
}
```

---

## **13. Pros vs Cons Summary Table**

| Pros ✅                      | Cons ❌                            |
| --------------------------- | --------------------------------- |
| Faster object creation      | Complex for deep objects          |
| No need to know exact class | Harder to debug                   |
| Runtime flexibility         | Can introduce hidden dependencies |
| Reduces boilerplate         | Maintenance overhead              |

---

## **14. Relation to Other Patterns**

| Pattern            | Relation                                           |
| ------------------ | -------------------------------------------------- |
| **Factory Method** | Creates new objects from scratch using subclasses. |
| **Prototype**      | Creates new objects by cloning existing ones.      |
| **Builder**        | Constructs complex objects step by step.           |

---

## ✨ **15. Real-World Example Summary**

| Domain           | Example                                         |
| ---------------- | ----------------------------------------------- |
| Games            | Clone player characters, terrain, power-ups     |
| Documents        | Duplicate templates with different data         |
| UI Design Tools  | Duplicate buttons, panels, forms                |
| Database Systems | Duplicate configuration or connection templates |

---

## **Final Takeaways**

> “Prototype Pattern lets you build new things fast — by starting from something that already works.”

*  Use it when creation is expensive.
*  Clone what already exists.
*  Modify the copy instead of rebuilding.
*  Great for high-performance, dynamic systems.
