#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0; // // Pure virtual function (abstract class)
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

// Simple Factory
class ShapeFactory {
public:
    static Shape* createShape(string type) {
        if (type == "circle") return new Circle();
        if (type == "square") return new Square();
        return nullptr;
    }
};

// Client
int main() {
    Shape* s1 = ShapeFactory::createShape("circle");
    if (s1) s1->draw();

    Shape* s2 = ShapeFactory::createShape("square");
    if (s2) s2->draw();

    delete s1;
    delete s2;
    return 0;
}

// 👉 ShapeFactory centralizes object creation. Client code doesn’t use new directly.