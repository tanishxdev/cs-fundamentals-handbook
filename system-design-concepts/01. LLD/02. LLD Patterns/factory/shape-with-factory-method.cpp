#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() override { cout << "Drawing Circle\n"; }
};

class Square : public Shape {
public:
    void draw() override { cout << "Drawing Square\n"; }
};

// Factory Method Base
class ShapeFactory {
public:
    virtual Shape* createShape() = 0; // Factory Method
    virtual ~ShapeFactory() {}
};

// Concrete Factories
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() override { return new Circle(); }
};

class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() override { return new Square(); }
};

// Client
int main() {
    ShapeFactory* factory1 = new CircleFactory();
    Shape* c = factory1->createShape();
    c->draw();

    ShapeFactory* factory2 = new SquareFactory();
    Shape* s = factory2->createShape();
    s->draw();

    delete c; delete s;
    delete factory1; delete factory2;
    return 0;
}

// 2️⃣ Factory Method
// 🚨 Problem

// Simple Factory still has if-else in factory class.
// If we add new product types → factory itself needs modification.

// ✅ Factory Method Solution

// Define a Creator (abstract) class.
// Let subclasses decide which object to create.

// ✅ Each factory subclass decides object creation.
// ✅ Adding new shapes → add new factory class (no changes in existing ones).