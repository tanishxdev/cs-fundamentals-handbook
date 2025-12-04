#include <iostream>
#include <string>

// Base abstract class for payment processing
class PaymentProcessor {
public:
    virtual void processPayment(double amount) = 0; // Pure virtual (must be overridden)
    virtual ~PaymentProcessor() = default; // Virtual destructor for safety
};

// Credit card payment processor (extension 1)
class CreditCardPaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
};

// PayPal payment processor (extension 2)
class PayPalPaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
};

// UPI payment processor (extension 3)
class UpiPaymentProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing UPI payment of ₹" << amount << std::endl;
    }
};

// Client code
int main() {
    // Use base class pointer for polymorphism
    PaymentProcessor* processor1 = new CreditCardPaymentProcessor();
    PaymentProcessor* processor2 = new PayPalPaymentProcessor();
    PaymentProcessor* processor3 = new UpiPaymentProcessor();

    // Each one processes differently without modifying base
    processor1->processPayment(100.50);
    processor2->processPayment(250.75);
    processor3->processPayment(5000.00);

    // Cleanup
    delete processor1;
    delete processor2;
    delete processor3;

    return 0;
}
