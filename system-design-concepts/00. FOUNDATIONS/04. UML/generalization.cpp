#include <iostream>
using namespace std;

// Generalized class (Superclass)
class BankAccount {
public:
    virtual void accountType() {   // virtual → enables polymorphism
        cout << "This is a general bank account" << endl;
    }
};

// Specialized classes (Subclasses)
class SavingsAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a savings account" << endl;
    }
};

class CurrentAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a current account" << endl;
    }
};

class CreditAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a credit account" << endl;
    }
};

int main() {
    // Polymorphic behavior
    BankAccount* b1 = new SavingsAccount();
    BankAccount* b2 = new CurrentAccount();
    BankAccount* b3 = new CreditAccount();

    b1->accountType();  // Savings
    b2->accountType();  // Current
    b3->accountType();  // Credit

    delete b1; delete b2; delete b3;
    return 0;
}
