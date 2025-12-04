#include <bits/stdc++.h>
using namespace std;

/**
===============================================================
                SOLID PRINCIPLES (C++ EXAMPLES)
===============================================================
S → Single Responsibility Principle  
O → Open / Closed Principle  
L → Liskov Substitution Principle  
I → Interface Segregation Principle  
D → Dependency Inversion Principle  
===============================================================
*/

/* -------------------------------------------------------------
   1️⃣ SRP — SINGLE RESPONSIBILITY PRINCIPLE
   One class = One responsibility only
--------------------------------------------------------------*/
class Invoice {
private:
    double amount;
public:
    Invoice(double amt) : amount(amt) {}
    double getAmount() const { return amount; }
};

// BAD: Writing invoice + saving invoice → multiple responsibilities
// GOOD: Separate class for saving (SRP)

class InvoiceSaver {
public:
    void saveToFile(const Invoice& inv) {
        cout << "[SRP] Invoice saved: Rs." << inv.getAmount() << endl;
    }
};


/* -------------------------------------------------------------
   2️⃣ OCP — OPEN/CLOSED PRINCIPLE
   Open for extension, closed for modification
--------------------------------------------------------------*/
class Discount {
public:
    virtual double apply(double amt) = 0;
    virtual ~Discount() {}
};

class NewUserDiscount : public Discount {
public:
    double apply(double amt) override { return amt * 0.90; } // 10% off
};

class SeasonalDiscount : public Discount {
public:
    double apply(double amt) override { return amt * 0.80; } // 20% off
};


/* -------------------------------------------------------------
   3️⃣ LSP — LISKOV SUBSTITUTION PRINCIPLE
   Child class should work wherever parent is expected
--------------------------------------------------------------*/
class Bird {
public:
    virtual void fly() = 0;
    virtual ~Bird() {}
};

class Sparrow : public Bird {
public:
    void fly() override { cout << "[LSP] Sparrow flying." << endl; }
};

// BAD example (violates LSP):
// class Ostrich : public Bird { void fly(){...cannot fly...}};


/* -------------------------------------------------------------
   4️⃣ ISP — INTERFACE SEGREGATION PRINCIPLE
   No class should be forced to implement unused methods
--------------------------------------------------------------*/
class IPrinter {
public:
    virtual void printDoc() = 0;
    virtual ~IPrinter() {}
};

class IScanner {
public:
    virtual void scanDoc() = 0;
    virtual ~IScanner() {}
};

class SimplePrinter : public IPrinter {
public:
    void printDoc() override {
        cout << "[ISP] Printing document..." << endl;
    }
};


/* -------------------------------------------------------------
   5️⃣ DIP — DEPENDENCY INVERSION PRINCIPLE
   High-level modules should depend on abstractions, not concrete classes
--------------------------------------------------------------*/
class IMessageSender {
public:
    virtual void sendMsg(string msg) = 0;
    virtual ~IMessageSender() {}
};

class EmailSender : public IMessageSender {
public:
    void sendMsg(string msg) override {
        cout << "[DIP] Sending Email: " << msg << endl;
    }
};

// High-level class depends on interface, not EmailSender directly
class Notification {
    IMessageSender* sender;
public:
    Notification(IMessageSender* s) : sender(s) {}
    void notify(string msg) {
        sender->sendMsg(msg);
    }
};


/* -------------------------------------------------------------
                        MAIN DEMO
--------------------------------------------------------------*/
int main() {
    cout << "==================== SOLID Principles ====================\n";

    // SRP
    Invoice inv(5000);
    InvoiceSaver saver;
    saver.saveToFile(inv);

    cout << "------------------------------------------------------------\n";

    // OCP
    Discount* d1 = new NewUserDiscount();
    Discount* d2 = new SeasonalDiscount();
    cout << "[OCP] New User Price: " << d1->apply(2000) << endl;
    cout << "[OCP] Seasonal Price: " << d2->apply(2000) << endl;
    delete d1;
    delete d2;

    cout << "------------------------------------------------------------\n";

    // LSP
    Bird* b = new Sparrow();
    b->fly();
    delete b;

    cout << "------------------------------------------------------------\n";

    // ISP
    SimplePrinter p;
    p.printDoc();

    cout << "------------------------------------------------------------\n";

    // DIP
    IMessageSender* mail = new EmailSender();
    Notification note(mail);
    note.notify("Your order has shipped!");
    delete mail;

    cout << "============================================================\n";
    cout << "All SOLID Principles Demonstrated Successfully!\n";

    return 0;
}

/*
===============================================================
EXPECTED OUTPUT
===============================================================
[SRP] Invoice saved: Rs.5000
[OCP] New User Price: 1800
[OCP] Seasonal Price: 1600
[LSP] Sparrow flying.
[ISP] Printing document...
[DIP] Sending Email: Your order has shipped!
===============================================================
KEY TAKEAWAYS
---------------------------------------------------------------
S → One class = One purpose  
O → Add new features without modifying existing code  
L → Derived classes must work where base is expected  
I → Split large interfaces into small ones  
D → High-level code depends on interfaces, not concrete classes  
===============================================================
*/
