#include <bits/stdc++.h>
using namespace std;

// base abstract class shape
class Shape{
public: 
    virtual double area() const = 0; // every shap must define area
    virtual ~Shape() = default; // virtual destructor
};

// derived class rectangle - Reactangle class 
class Rectangle : public Shape{
protected: 
    double width, height;
public: 
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
};

// derived class circle - Circle class
class Circle : public Shape{
protected: 
    double radius;
public: 
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14 * radius * radius; }
};
// Square class
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() const override {
        return side * side;
    }
};
int main()
{
    Shape* rect = new Rectangle(2, 3);
    Shape* crl = new Circle(5);
    Shape* sq = new Square(4);
    
    cout << "Rectangle area: " << rect->area() << endl;
    cout << "Circle area: " << crl->area() << endl;
    cout << "Square area: " << sq->area() << endl;

    delete rect;
    delete crl;
    delete sq;
    return 0;
}