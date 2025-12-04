#include <iostream>
using namespace std;

// Base Class
class PaymentGateway {
public:
    // Template Method
    void processPayment() {
        validateUser();
        initiateTransaction();
        doPayment();         // step differs
        sendConfirmation();
    }

    void validateUser() { cout << "Validating user credentials...\n"; }
    void initiateTransaction() { cout << "Initiating transaction...\n"; }
    void sendConfirmation() { cout << "Sending payment confirmation...\n"; }

    // Abstract step (implemented by subclasses)
    virtual void doPayment() = 0;
};

// Concrete Class 1: Credit Card Payment
class CreditCardPayment : public PaymentGateway {
public:
    void doPayment() override {
        cout << "Processing payment through Credit Card...\n";
    }
};

// Concrete Class 2: UPI Payment
class UPIPayment : public PaymentGateway {
public:
    void doPayment() override {
        cout << "Processing payment through UPI...\n";
    }
};

// Concrete Class 3: PayPal Payment
class PayPalPayment : public PaymentGateway {
public:
    void doPayment() override {
        cout << "Processing payment through PayPal...\n";
    }
};

// Client
int main() {
    cout << "--- Credit Card Payment ---\n";
    CreditCardPayment cc;
    cc.processPayment();

    cout << "\n--- UPI Payment ---\n";
    UPIPayment upi;
    upi.processPayment();

    cout << "\n--- PayPal Payment ---\n";
    PayPalPayment paypal;
    paypal.processPayment();

    return 0;
}
