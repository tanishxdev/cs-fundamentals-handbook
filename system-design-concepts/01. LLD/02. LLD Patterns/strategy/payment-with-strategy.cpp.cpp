#include <iostream>
using namespace std;

// 1. Strategy Interface
class PaymentMethod {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentMethod() {}
};

// 2. Concrete Strategies
class CreditCardPay : public PaymentMethod {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card.\n";
    }
};

class PayPalPay : public PaymentMethod {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using PayPal.\n";
    }
};

// 3. Context (uses Strategy)
class PaymentProcessor {
private:
    PaymentMethod* method; // HAS-A Strategy
public:
    void setMethod(PaymentMethod* m) {
        method = m;
    }
    void pay(double amount) {
        if (method) method->pay(amount);
        else cout << "No payment method selected!\n";
    }
};

// 4. Client
int main() {
    PaymentProcessor processor;

    CreditCardPay credit;
    PayPalPay paypal;

    processor.setMethod(&credit);
    processor.pay(1000);

    processor.setMethod(&paypal);
    processor.pay(50);

    return 0;
}
// Strategy Design Pattern Solution

// 👉 Strategy Pattern says:
// Define a family of algorithms (strategies), put each in a separate class, and make them interchangeable.

// ✨ Benefits of Strategy Pattern

// No big if-else → code is clean & extendable.
// Easy to add new strategies (UPI, Bitcoin, etc.) without changing existing code.
// Follows OCP and DIP (Open-Closed & Dependency Inversion Principles).