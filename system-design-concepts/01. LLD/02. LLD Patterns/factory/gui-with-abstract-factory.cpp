#include <iostream>
using namespace std;

// Abstract Products
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};

// Concrete Products (Windows)
class WindowsButton : public Button {
public:
    void render() override { cout << "Windows Button\n"; }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override { cout << "Windows Checkbox\n"; }
};

// Concrete Products (Mac)
class MacButton : public Button {
public:
    void render() override { cout << "Mac Button\n"; }
};

class MacCheckbox : public Checkbox {
public:
    void render() override { cout << "Mac Checkbox\n"; }
};

// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override { return new WindowsButton(); }
    Checkbox* createCheckbox() override { return new WindowsCheckbox(); }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    Checkbox* createCheckbox() override { return new MacCheckbox(); }
};

// Client
int main() {
    GUIFactory* factory;

    // Suppose OS = Windows
    factory = new WindowsFactory();
    Button* b1 = factory->createButton();
    Checkbox* c1 = factory->createCheckbox();
    b1->render();
    c1->render();

    // Suppose OS = Mac
    factory = new MacFactory();
    Button* b2 = factory->createButton();
    Checkbox* c2 = factory->createCheckbox();
    b2->render();
    c2->render();

    return 0;
}

// 3️⃣ Abstract Factory
// 🚨 Problem

// Now imagine we want families of related products.
// Example: UI Toolkit with Buttons and Checkboxes.

// We need different families:
// Windows-style UI
// Mac-style UI

// ✅ Abstract Factory Solution

// Provide an interface for creating families of related objects.
// Concrete factories implement the interface.