#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

- Abstraction allows us to define **high-level interfaces** that describe *what operations* a system supports,
  while hiding *how those operations* are implemented.

- It lets different modules follow the **same contract**, promoting **loose coupling** and **scalable design**.

In other words:
> “Define behavior, not implementation.”

👉 Why It Matters (Real System Context)

| Without Abstraction | With Abstraction |
| -------------------- | ---------------- |
| Every payment type (Card, PayPal, UPI) has its own functions → high coupling, duplicate code. | A unified Payment interface → consistent and extensible system. |
| Hard to add new payment methods. | Easy to extend without modifying existing code. |
| Tight integration with implementation logic. | Only interface (contract) is visible to main system. |

👉 Real-life Analogy

When you make an **online payment**, you just click *“Pay”*.  
You don’t know whether it’s processed via UPI, Card, or PayPal.  
All you need is a *common interface (Pay)* — that’s **abstraction**.

👉 Problem Statement

Design a Payment Processing System where:
1. All payment methods (CreditCard, PayPal, UPI) implement a common interface.
2. The main program processes payment **without knowing** which payment type is used.
3. Each payment type hides its internal implementation details.
*/

 /*
------------------------------------------------------------
Problem: Demonstrate Complex Abstraction using Payment System
------------------------------------------------------------
Goal:
1. Define an abstract class 'Payment' that declares the common interface.
2. Derived classes implement the behavior for each payment type.
3. The main system uses abstraction to process all payments uniformly.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// ABSTRACT CLASS: Payment
// Defines the interface (contract) for all payment types
// ----------------------------------------------------------
class Payment {
public:
    // Pure virtual functions (must be implemented by derived classes)
    virtual void authenticateUser() = 0;
    virtual void processPayment(double amount) = 0;
    virtual void sendReceipt() = 0;

    // Concrete (shared) function
    void startPayment(double amount) {
        cout << "\n--- Initiating Payment of Rs. " << amount << " ---\n";
        authenticateUser();      // Step 1: authentication
        processPayment(amount);  // Step 2: process
        sendReceipt();           // Step 3: confirmation
        cout << "----------------------------------------------\n";
    }

    // Virtual destructor (important for cleanup)
    virtual ~Payment() {}
};

// ----------------------------------------------------------
// DERIVED CLASS: CreditCardPayment
// Implements Payment interface for credit card transactions
// ----------------------------------------------------------
class CreditCardPayment : public Payment {
private:
    string cardNumber, cvv;

public:
    CreditCardPayment(string cardNum, string cvvCode)
        : cardNumber(cardNum), cvv(cvvCode) {}

    void authenticateUser() override {
        cout << "Authenticating Credit Card credentials..." << endl;
        cout << "Card Verified Successfully!" << endl;
    }

    void processPayment(double amount) override {
        cout << "Processing Credit Card Payment of Rs. " << amount << " ..." << endl;
        cout << "Transaction Approved!" << endl;
    }

    void sendReceipt() override {
        cout << "Sending Credit Card Payment Receipt to user..." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: PayPalPayment
// Implements Payment interface for PayPal
// ----------------------------------------------------------
class PayPalPayment : public Payment {
private:
    string email;

public:
    PayPalPayment(string emailAddress) : email(emailAddress) {}

    void authenticateUser() override {
        cout << "Logging into PayPal account: " << email << endl;
        cout << "Authentication Successful!" << endl;
    }

    void processPayment(double amount) override {
        cout << "Transferring Rs. " << amount << " via PayPal..." << endl;
        cout << "Payment Completed Successfully!" << endl;
    }

    void sendReceipt() override {
        cout << "Sending PayPal Payment Confirmation Email..." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: UPIPayment
// Implements Payment interface for UPI transactions
// ----------------------------------------------------------
class UPIPayment : public Payment {
private:
    string upiId;

public:
    UPIPayment(string id) : upiId(id) {}

    void authenticateUser() override {
        cout << "Verifying UPI ID: " << upiId << endl;
        cout << "PIN Verified Successfully!" << endl;
    }

    void processPayment(double amount) override {
        cout << "Transferring Rs. " << amount << " via UPI..." << endl;
        cout << "Payment Successful!" << endl;
    }

    void sendReceipt() override {
        cout << "Sending UPI Transaction SMS..." << endl;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates Abstraction with multiple derived classes
// ----------------------------------------------------------
int main() {
    // Abstract pointer (common interface for all payments)
    vector<Payment*> payments;

    // Create objects of different payment types
    payments.push_back(new CreditCardPayment("1234-5678-9999", "321"));
    payments.push_back(new PayPalPayment("user@example.com"));
    payments.push_back(new UPIPayment("alice@upi"));

    // Process all payments uniformly
    for (auto p : payments) {
        p->startPayment(5000); // Common interface call
        delete p;              // Free memory
    }

    return 0;
}

/*
👉 Step-by-Step Flow

1. The abstract class `Payment` defines **what operations** every payment must have.
2. Each derived class implements **how** those operations work.
3. `main()` doesn’t care which payment type is being processed — it just calls `startPayment()`.
4. This makes the system **extensible** — new payment types can be added easily.

👉 Example Output

--- Initiating Payment of Rs. 5000 ---
Authenticating Credit Card credentials...
Card Verified Successfully!
Processing Credit Card Payment of Rs. 5000 ...
Transaction Approved!
Sending Credit Card Payment Receipt to user...
----------------------------------------------

--- Initiating Payment of Rs. 5000 ---
Logging into PayPal account: user@example.com
Authentication Successful!
Transferring Rs. 5000 via PayPal...
Payment Completed Successfully!
Sending PayPal Payment Confirmation Email...
----------------------------------------------

--- Initiating Payment of Rs. 5000 ---
Verifying UPI ID: alice@upi
PIN Verified Successfully!
Transferring Rs. 5000 via UPI...
Payment Successful!
Sending UPI Transaction SMS...
----------------------------------------------

👉 Key Takeaways

| Concept                            | Description |
| ---------------------------------- | ------------ |
| **Abstract Class**                 | Defines the interface (contract) — what functions must exist. |
| **Derived Classes**                | Implement the abstract functions — how behavior works. |
| **Loose Coupling**                 | Main code depends only on the abstract interface. |
| **Extensibility**                  | Add new payment types (NetBanking, CryptoPayment, etc.) without changing main logic. |

👉 How It Connects to System Design

- In real systems, you never hardcode each payment method.
- Instead, you design a **common abstract layer (PaymentGatewayInterface)**.
- Each vendor (Razorpay, PayPal, Stripe) implements it separately.
- Business logic (main program) calls the interface — not the implementation.

This allows for:
✅ Scalability  
✅ Maintainability  
✅ Low coupling between modules  
✅ High cohesion within modules
*/
