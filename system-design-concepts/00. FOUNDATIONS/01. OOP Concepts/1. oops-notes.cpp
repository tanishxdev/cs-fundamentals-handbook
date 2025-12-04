#include <bits/stdc++.h>
using namespace std;
/**
=====================================================================
      ALL FOUR PILLARS OF OBJECT-ORIENTED PROGRAMMING
=====================================================================
1️⃣ **Encapsulation** → Hiding data using private members & getters/setters  
2️⃣ **Abstraction**   → Showing only necessary details via abstract classes  
3️⃣ **Inheritance**   → Reusing and extending parent class functionality  
4️⃣ **Polymorphism**  → Same interface, different behavior
=====================================================================
*/

// ---------------------------------------------------------------
// 1️⃣ ENCAPSULATION — Data Hiding and Controlled Access
// ---------------------------------------------------------------
class Account {
private:
    string owner;
    double balance;

public:
    // Constructor
    Account(string o, double b) : owner(o), balance(b) {}

    // Setter with validation
    void deposit(double amount) {
        if (amount > 0) balance += amount;
        else cout << "Invalid deposit!" << endl;
    }

    // Getter (read-only access)
    double getBalance() const {
        return balance;
    }

    void showDetails() const {
        cout << "[Encapsulation] Account Owner: " << owner
             << " | Balance: " << balance << endl;
    }
};

// ---------------------------------------------------------------
// 2️⃣ ABSTRACTION — Hiding Complex Logic Behind Interface
// ---------------------------------------------------------------
class Payment {
public:
    virtual void processPayment(double amount) = 0; // abstract method
    virtual ~Payment() {}
};

class CreditCardPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "[Abstraction] Paying Rs." << amount << " via Credit Card." << endl;
    }
};

// ---------------------------------------------------------------
// 3️⃣ INHERITANCE — Reusing Parent Functionality
// ---------------------------------------------------------------
class Animal {
public:
    void eat() { cout << "[Inheritance] Animal is eating..." << endl; }
};

class Dog : public Animal {
public:
    void bark() { cout << "[Inheritance] Dog is barking..." << endl; }
};
class Lion : public Animal {
public:
    void Roar() { cout << "[Inheritance] Lion is barking..." << endl; }
};

// ---------------------------------------------------------------
// 4️⃣ POLYMORPHISM — Same Interface, Different Behavior
// ---------------------------------------------------------------
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() override { cout << "[Polymorphism] Drawing a Circle." << endl; }
};

class Rectangle : public Shape {
public:
    void draw() override { cout << "[Polymorphism] Drawing a Rectangle." << endl; }
};

// ---------------------------------------------------------------
// MAIN — Demonstrating all OOP concepts together
// ---------------------------------------------------------------
int main() {
    cout << "==================== OOPs in Short ====================\n";

    // 1️⃣ Encapsulation
    Account acc("Alice", 5000);
    acc.deposit(1500);
    acc.showDetails();

    cout << "--------------------------------------------------------\n";

    // 2️⃣ Abstraction
    Payment* pay = new CreditCardPayment();
    pay->processPayment(2500);
    delete pay;

    cout << "--------------------------------------------------------\n";

    // 3️⃣ Inheritance
    Dog dog;
    dog.eat();   // inherited from Animal
    dog.bark();  // Dog’s own behavior

    Lion lion;
    // lion.eat();   // inherited from Animal
    lion.Roar();  // Lion’s own behavior

    cout << "--------------------------------------------------------\n";

    // 4️⃣ Polymorphism
    vector<Shape*> shapes;
    shapes.push_back(new Circle());
    shapes.push_back(new Rectangle());

    for (auto s : shapes) {
        s->draw();   // same call → different behavior
        delete s;
    }

    cout << "========================================================\n";
    cout << "All OOPs Concepts Demonstrated Successfully!\n";

    return 0;
}

/*
=====================================================================
👉 OUTPUT (Expected)

==================== OOPs in Short ====================
[Encapsulation] Account Owner: Alice | Balance: 6500
--------------------------------------------------------
[Abstraction] Paying Rs.2500 via Credit Card.
--------------------------------------------------------
[Inheritance] Animal is eating...
[Inheritance] Dog is barking...
--------------------------------------------------------
[Polymorphism] Drawing a Circle.
[Polymorphism] Drawing a Rectangle.
========================================================
All OOPs Concepts Demonstrated Successfully!

=====================================================================
👉 KEY TAKEAWAYS

| Concept           | Meaning / Example |
|----------------   |-------------------|
| **Encapsulation** | Bundling data + methods (Account with private balance). |
| **Abstraction**   | Exposing essential operations, hiding implementation (Payment interface). |
| **Inheritance**   | Code reuse and hierarchy (Dog inherits from Animal). |
| **Polymorphism**  | One interface → many forms (Shape → Circle, Rectangle). |

✅ These four pillars together build **modular, maintainable, and scalable system designs.**
=====================================================================
*/
