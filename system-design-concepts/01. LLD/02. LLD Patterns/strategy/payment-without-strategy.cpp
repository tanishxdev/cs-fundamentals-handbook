#include <iostream>
using namespace std;

class Payment {
public:
    void pay(string method, double amount) {
        if (method == "CreditCard") {
            cout << "Paid " << amount << " using Credit Card.\n";
        } 
        else if (method == "PayPal") {
            cout << "Paid " << amount << " using PayPal.\n";
        }
        else {
            cout << "Invalid Payment Method!\n";
        }
    }
};

int main() {
    Payment p;
    p.pay("CreditCard", 1000);
    p.pay("PayPal", 500);
    return 0;
}

// 🚨 Problem Without Strategy Pattern

// Imagine we are building a Payment System for an e-commerce app.
// We support CreditCard and PayPal payments.

// ⚠️ Problem

// Adding new payment methods (e.g., UPI, Bitcoin) → need to modify existing class (breaks OCP: Open/Closed Principle).

// Class becomes large and messy (too many if-else).

// Hard to extend without rewriting code.