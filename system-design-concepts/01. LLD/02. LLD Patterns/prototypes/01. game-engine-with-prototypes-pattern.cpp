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
        cout << "Drawing a " << color << " circle.\n";
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
