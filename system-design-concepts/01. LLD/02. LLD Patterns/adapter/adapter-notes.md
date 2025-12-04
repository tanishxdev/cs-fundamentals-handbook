# 🎯 **Adapter Pattern**

### **Definition**

Adapter is a **structural design pattern** that converts one interface into another that the client expects.
It’s like a **plug adapter** that allows two incompatible interfaces to work together.

---

## ✅ **Why Adapter?**

* When you want to use an existing class but its interface doesn’t match the one you need.
* Helps integrate **legacy code** with new systems.
* Common in frameworks and libraries (connecting incompatible APIs).

---

## 📌 **Real-Life Examples**

1. **Power Adapter**: Converts 2-pin plug to 3-pin plug.
2. **USB-to-HDMI Adapter**: Converts one type of interface to another.
3. **Software Example**: Wrapping an old API (`OldPaymentGateway`) so it can work with new API (`NewPaymentSystem`).

---

## ✅ **C++ Example: Payment Adapter**

Suppose we have a new payment system, but we need to use an old legacy gateway as well.

```cpp
#include <iostream>
using namespace std;

// ---------------- Legacy System ----------------
class OldPaymentGateway {
public:
    void makePayment(int amount) {
        cout << "Payment of Rs." << amount << " processed using Old Gateway.\n";
    }
};

// ---------------- Target Interface ----------------
class NewPaymentSystem {
public:
    virtual void pay(int amount) = 0;
    virtual ~NewPaymentSystem() {}
};

// ---------------- Adapter ----------------
class PaymentAdapter : public NewPaymentSystem {
private:
    OldPaymentGateway* oldGateway;
public:
    PaymentAdapter(OldPaymentGateway* gateway) : oldGateway(gateway) {}
    
    void pay(int amount) override {
        // Adapting old method to new method
        oldGateway->makePayment(amount);
    }
};

// ---------------- Client Code ----------------
int main() {
    // Using new interface directly
    NewPaymentSystem* payment = nullptr;

    // Suppose we still need to use old gateway
    OldPaymentGateway* oldGateway = new OldPaymentGateway();
    payment = new PaymentAdapter(oldGateway);

    payment->pay(500);  // Client thinks it's using "NewPaymentSystem"

    delete payment;
    delete oldGateway;
    return 0;
}
```

---

### ✅ **Output**

```
Payment of Rs.500 processed using Old Gateway.
```

---

## 🔑 **Key Points**

* **Client** expects `NewPaymentSystem`.
* **OldPaymentGateway** has a different method name (`makePayment`).
* **Adapter (PaymentAdapter)** converts `pay()` calls into `makePayment()` calls.
* Client stays unaware of the adaptation.

---

⚡ This is widely used in:

* **Connecting legacy code** with modern systems.
* **Adapting 3rd party libraries** (e.g., integrating different logging/payment/database APIs).
* **UI frameworks** where you need to adapt widgets.
