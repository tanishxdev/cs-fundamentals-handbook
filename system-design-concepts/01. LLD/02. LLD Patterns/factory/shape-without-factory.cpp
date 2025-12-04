#include <bits/stdc++.h>
using namespace std;
class Circle {
public:
    void draw() { cout << "Drawing Circle" << endl; }
};

class Square {
public:
    void draw() { cout << "Drawing Square" << endl; }
};

int main()
{
    string shapeType;
    // cout << "Enter shape (Circle/Square): ";
    cin >> shapeType;
    if (shapeType == "Circle") {
        Circle c;
        c.draw();
    } else if (shapeType == "Square") {
        Square s;
        s.draw();
    } else {
        cout << "Unknown shape!" << endl;
    }    
    return 0;
}

// 🎯 Factory Pattern
// The Factory family has 3 levels:

// Simple Factory (not part of GoF officially, but widely used)
// Factory Method (GoF Creational Pattern)
// Abstract Factory (GoF Creational Pattern, advanced)

// ❌ Without Factory
// 🚨 Problem
//
// Suppose we want to build a Shape Drawing App (circle, square).
// We directly use `if-else` in client code to decide which object to create.
//
// ⚠️ Problem:
// - Every time we add a new shape → need to modify client code.
// - Violates OCP (Open-Closed Principle).
// - Too many `if-else` statements → messy, hard to maintain.


// 1️⃣ Simple Factory
// ✅ Solution
//
// Introduce a central Factory class that decides which object to create.
// Client code asks Factory for an object instead of using `new` directly.
//
// ✨ Benefits:
// - Client doesn’t care about object creation details.
// - Code is cleaner and centralized.
//
// ⚠️ Limitation:
// - Still has `if-else` inside Factory.
// - Adding new shapes → modify Factory (so partial OCP violation).

// 2️⃣ Factory Method
// ✅ Solution
//
// Define an abstract Factory interface with a `createShape()` method.
// Concrete factories (CircleFactory, SquareFactory, etc.) decide which object to create.
//
// ✨ Benefits:
// - Removes `if-else` from a single factory.
// - Adding new shapes → create new factory class (no changes in old code).
// - Strictly follows OCP and DIP.
//
// ⚠️ Limitation:
// - More classes needed (one factory per product).
// - Slightly more complex than Simple Factory.

// 3️⃣ Abstract Factory
// ✅ Solution
//
// Used when we want to create **families of related objects** (e.g., Buttons + Checkboxes).
// Define an Abstract Factory interface with multiple creation methods.
// Concrete factories (WindowsFactory, MacFactory) create consistent families.
//
// ✨ Benefits:
// - Ensures related objects are created together (WindowsButton + WindowsCheckbox).
// - Easy to switch entire product families at once.
// - Follows OCP, DIP, SRP.
//
// ⚠️ Limitation:
// - More complex, many classes/interfaces.
// - Best for systems with multiple families of products.


// 🔑 Summary

// Without Factory → har jagah if-else.
// Simple Factory → ek centralized class jo if-else handle karti hai.
// Factory Method → if-else hata diya, har product ke liye alag factory banayi.
// Abstract Factory → families of related products (not just ek product).