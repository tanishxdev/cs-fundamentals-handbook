#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

**Polymorphism** lets us treat different objects (like Circle, Rectangle, Triangle)
through a single, common interface (Shape).  

Each shape implements its own version of `draw()` and `area()` —  
but the main program doesn’t need to know which shape it’s working with.

This is called **Run-Time Polymorphism** (achieved using virtual functions).

👉 Why Needed

| Without Polymorphism | With Polymorphism |
| --------------------- | ---------------- |
| Each shape would need separate code to call draw() and area(). | One base pointer (Shape*) can call methods for all derived classes. |
| Hard to extend when new shapes are added. | New shapes can be added without modifying main logic. |
| Code duplication for each shape type. | Common interface ensures cleaner, reusable design. |

👉 Real-life Analogy

Think of a **Graphics Editor** like Photoshop:
- You can select *any* shape (circle, rectangle, line).
- When you press “Draw,” the editor doesn’t care which shape it is —  
  each shape knows **how to draw itself**.  

That’s **polymorphism** in action — same call, different behavior.

👉 Problem Statement

Create a Shape system where:
1. Base class `Shape` defines a common interface (draw(), area()).
2. Derived classes (`Circle`, `Rectangle`, `Triangle`) implement them differently.
3. Main function calls them using base class pointers to demonstrate runtime polymorphism.
*/

/*
------------------------------------------------------------
Problem: Real-world Polymorphism — Shape Drawing System
------------------------------------------------------------
Goal:
1. Use runtime polymorphism to handle multiple shape types uniformly.
2. Demonstrate overriding of methods (draw and area).
3. Show extensibility — new shapes can be added easily.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// BASE CLASS: Shape (Abstract)
// Defines the interface (contract) for all shapes
// ----------------------------------------------------------
class Shape {
public:
    // Pure virtual functions — must be implemented by all derived classes
    virtual void draw() = 0;
    virtual double area() = 0;

    // Virtual destructor
    virtual ~Shape() {}
};

// ----------------------------------------------------------
// DERIVED CLASS: Circle
// Implements Shape interface for Circle
// ----------------------------------------------------------
class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r) {}

    void draw() override {
        cout << "Drawing Circle with radius: " << radius << endl;
    }

    double area() override {
        return 3.14159 * radius * radius;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Rectangle
// Implements Shape interface for Rectangle
// ----------------------------------------------------------
class Rectangle : public Shape {
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    void draw() override {
        cout << "Drawing Rectangle (L=" << length << ", W=" << width << ")" << endl;
    }

    double area() override {
        return length * width;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Triangle
// Implements Shape interface for Triangle
// ----------------------------------------------------------
class Triangle : public Shape {
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    void draw() override {
        cout << "Drawing Triangle (Base=" << base << ", Height=" << height << ")" << endl;
    }

    double area() override {
        return 0.5 * base * height;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates Polymorphism using Shapes
// ----------------------------------------------------------
int main() {
    // Create different shape objects
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));
    shapes.push_back(new Triangle(3.0, 7.0));

    // Common interface — no need to know actual type
    cout << "----- Drawing Shapes and Calculating Areas -----" << endl;
    for (Shape* s : shapes) {
        s->draw();                         // Runtime polymorphism
        cout << "Area: " << s->area() << endl;
        cout << "----------------------------------------------" << endl;
    }

    // Cleanup
    for (Shape* s : shapes)
        delete s;

    return 0;
}

/*
👉 Step-by-Step Flow

1. `Shape` acts as the **abstract base class** (common interface).
2. Each derived class (`Circle`, `Rectangle`, `Triangle`) provides its own implementation for:
   - `draw()` → visual representation
   - `area()` → shape-specific formula
3. In `main()`, a **vector of Shape pointers** stores different shapes.
4. Each `Shape*` points to a different derived object → runtime polymorphism.
5. The same call (`s->draw()` / `s->area()`) produces different results depending on the actual object.

👉 Example Output

----- Drawing Shapes and Calculating Areas -----
Drawing Circle with radius: 5
Area: 78.5398
----------------------------------------------
Drawing Rectangle (L=4, W=6)
Area: 24
----------------------------------------------
Drawing Triangle (Base=3, Height=7)
Area: 10.5
----------------------------------------------

👉 Key Takeaways

| Concept | Description |
| -------- | ------------ |
| **Polymorphism** | Same interface (`Shape*`) behaves differently for each derived type. |
| **Pure Virtual Functions** | Force derived classes to implement core behaviors (`draw()`, `area()`). |
| **Abstract Class** | Defines the “what” without “how” — like a blueprint. |
| **Extensibility** | Easily add `Square`, `Ellipse`, etc. without modifying existing code. |

👉 How This Maps to System Design

In real-world architecture:
- Base class = **Interface / Abstract Service**  
- Derived class = **Concrete Implementations**

**Example:**
- `PaymentService` → abstract class with `processPayment()`.
- Derived: `StripeService`, `RazorpayService`, `PayPalService`.
- The system just calls:
  ```cpp
  PaymentService* p = new StripeService();
  p->processPayment();

  → The system never changes — only new implementations are added.
*/