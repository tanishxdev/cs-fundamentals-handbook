# 🏭 Notification System Using Factory Method Pattern

### 1️⃣ Product Interface

```cpp
#include <iostream>
using namespace std;

// Abstract Product
class Notification {
public:
    virtual void notifyUser() = 0; // pure virtual function
    virtual ~Notification() {}
};
```

* `Notification` is the **common interface** for all notification types.
* Every notification must implement `notifyUser()`.

---

### 2️⃣ Concrete Products

```cpp
class EmailNotification : public Notification {
public:
    void notifyUser() override {
        cout << "Sending an Email notification" << endl;
    }
};

class SMSNotification : public Notification {
public:
    void notifyUser() override {
        cout << "Sending an SMS notification" << endl;
    }
};

class PushNotification : public Notification {
public:
    void notifyUser() override {
        cout << "Sending a Push notification" << endl;
    }
};
```

* These are **specific notification types**.
* Each implements the `notifyUser()` method differently.

---

### 3️⃣ Creator Interface (Factory Interface)

```cpp
class NotificationFactory {
public:
    virtual Notification* createNotification() = 0;
    virtual ~NotificationFactory() {}
};
```

* Defines a **factory method** `createNotification()`.
* Subclasses will **decide which notification to create**.

---

### 4️⃣ Concrete Factories

```cpp
class EmailFactory : public NotificationFactory {
public:
    Notification* createNotification() override {
        return new EmailNotification();
    }
};

class SMSFactory : public NotificationFactory {
public:
    Notification* createNotification() override {
        return new SMSNotification();
    }
};

class PushFactory : public NotificationFactory {
public:
    Notification* createNotification() override {
        return new PushNotification();
    }
};
```

* Each factory is responsible for creating its **specific notification type**.

---

### 5️⃣ Client Code

```cpp
int main() {
    // Email notification
    NotificationFactory* emailFactory = new EmailFactory();
    Notification* email = emailFactory->createNotification();
    email->notifyUser();
    delete email;
    delete emailFactory;

    // SMS notification
    NotificationFactory* smsFactory = new SMSFactory();
    Notification* sms = smsFactory->createNotification();
    sms->notifyUser();
    delete sms;
    delete smsFactory;

    // Push notification
    NotificationFactory* pushFactory = new PushFactory();
    Notification* push = pushFactory->createNotification();
    push->notifyUser();
    delete push;
    delete pushFactory;

    return 0;
}
```

✅ **Output:**

```
Sending an Email notification
Sending an SMS notification
Sending a Push notification
```

---

### ⚡ Advantages of This Approach

| Advantage                 | Explanation                                                                     |
| ------------------------- | ------------------------------------------------------------------------------- |
| **Loose Coupling**        | Client only depends on `Notification` interface, not concrete classes.          |
| **Scalable**              | Add `WhatsAppNotification` by creating new class + factory — no client changes. |
| **Cleaner Code**          | No messy `if-else` in client code.                                              |
| **Single Responsibility** | Factories handle object creation, client handles usage only.                    |

---

This is a **real-life scenario**: think of any app like **Amazon, Instagram, or Twitter** — they might send notifications through multiple channels, and the Factory Method lets them **easily switch or add channels** without touching client logic.

---
