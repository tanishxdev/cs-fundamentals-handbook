# 🎯 What is Bridge Pattern?

The **Bridge Pattern** is a **structural design pattern**.

👉 It **decouples abstraction from implementation** so both can evolve independently.

---

## 🔴 The Problem

Suppose we want to build a system for **different shapes** (`Circle`, `Square`) and each shape can be **drawn in different colors** (`Red`, `Blue`).

* If we directly combine them, we’ll end up with a **class explosion**:

  * `RedCircle`, `BlueCircle`, `RedSquare`, `BlueSquare` … 🚨

That’s **not scalable** if shapes × colors keep growing.

---

## 🟢 The Solution (Bridge)

* Separate **Abstraction (Shape)** from **Implementation (Color)**.
* Use **composition (HAS-A)** instead of inheritance.
* The `Shape` class contains a reference to `Color`.
* So, we can mix & match at runtime.

---

## ✅ C++ Implementation

```cpp
#include <iostream>
using namespace std;

// ---------------- Implementation Hierarchy ----------------
class Color {
public:
    virtual void applyColor() = 0;
    virtual ~Color() {}
};

class Red : public Color {
public:
    void applyColor() override {
        cout << "Applying Red Color" << endl;
    }
};

class Blue : public Color {
public:
    void applyColor() override {
        cout << "Applying Blue Color" << endl;
    }
};

// ---------------- Abstraction Hierarchy ----------------
class Shape {
protected:
    Color* color;  // Bridge to implementation
public:
    Shape(Color* c) : color(c) {}
    virtual void draw() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    Circle(Color* c) : Shape(c) {}
    void draw() override {
        cout << "Drawing Circle with ";
        color->applyColor();
    }
};

class Square : public Shape {
public:
    Square(Color* c) : Shape(c) {}
    void draw() override {
        cout << "Drawing Square with ";
        color->applyColor();
    }
};

// ---------------- Client Code ----------------
int main() {
    Color* red = new Red();
    Color* blue = new Blue();

    Shape* circle = new Circle(red);
    Shape* square = new Square(blue);

    circle->draw();   // Drawing Circle with Red
    square->draw();   // Drawing Square with Blue

    // cleanup
    delete circle;
    delete square;
    delete red;
    delete blue;

    return 0;
}
```

---

## ✅ Output

```
Drawing Circle with Applying Red Color
Drawing Square with Applying Blue Color
```

---

## 🔑 Key Points

* **Abstraction (Shape)**: Defines high-level operations.
* **Implementation (Color)**: Defines low-level operations.
* **Bridge (Composition)**: Shape **HAS-A** Color, instead of inheriting.
* Both hierarchies can grow **independently**.

---

⚡ **Where is Bridge Used?**

* **GUI frameworks** (e.g., Button abstraction + OS-specific implementations).
* **Database drivers** (e.g., DB abstraction + MySQL/Oracle/Postgres implementations).
* **Graphics/Rendering engines** (Shape abstraction + Render in OpenGL/DirectX).
