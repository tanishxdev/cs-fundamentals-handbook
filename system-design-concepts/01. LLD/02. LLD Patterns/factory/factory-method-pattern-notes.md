# Factory Method Class Diagram

## 🎯 **1. What is the Factory Method Pattern (Core Idea)**

**Definition:**
Factory Method is a **Creational Design Pattern** that defines an **interface for creating objects**, but **lets subclasses decide which class to instantiate**.

✅ **Meaning in simple words:**

> Instead of directly creating objects using `new`, we use a **factory (creator)** that creates the objects for us.
> The **type of object** to create is decided by **subclasses or conditions**, **not the client code**.

---

## 💡 **2. Why We Need It**

Let’s understand *the problem* before the pattern.

### Example without Factory Pattern:

Suppose you’re creating a **Vehicle app** that can handle:

* TwoWheelers
* FourWheelers

If you write this directly:

```js
if (type === "two") return new TwoWheeler();
else if (type === "four") return new FourWheeler();
```

Then your **client code** depends directly on **concrete classes**.
Adding a new type (e.g., `ThreeWheeler`) means you must modify the client code again — this **breaks the Open/Closed Principle (OCP)**.

---

## 🧩 **3. The Factory Method Solution**

We **delegate object creation** to a **factory**.

* Define a **common interface (Vehicle)**
* Implement **Concrete classes** (TwoWheeler, FourWheeler)
* Define a **factory interface (VehicleFactory)** with a method `createVehicle()`
* Implement **specific factories** (TwoWheelerFactory, FourWheelerFactory)
* Client just uses the factory — **no need to know which class is being created**

---

## 🧱 **4. Structure of the Factory Method Pattern**

| Component               | Description                                                           |
| ----------------------- | --------------------------------------------------------------------- |
| **Product (Interface)** | Common interface for all products (e.g., `Vehicle`)                   |
| **Concrete Product**    | Specific implementations (`TwoWheeler`, `FourWheeler`)                |
| **Creator (Factory)**   | Declares factory method (`createVehicle()`)                           |
| **Concrete Creator**    | Implements the factory method to create specific product              |
| **Client**              | Uses the factory to get objects — doesn’t care which subclass it gets |

---

## 🧠 **5. Intuition Behind It**

Think of it like an **order counter** in a restaurant:

* You (the customer/client) say, “I want a burger.”
* The **kitchen (factory)** decides *which chef* and *what ingredients* to use.
* You get your **Burger (product)** — without knowing its creation logic.

Similarly, in code:

* Client says: “I want a Vehicle.”
* Factory decides whether to create a TwoWheeler or FourWheeler.
* Client just gets a ready-to-use object.

---

## 🪶 **6. Step-by-Step Dry Run of Example**

### Step 1: Client asks for a TwoWheeler

```js
const twoWheelerFactory = new TwoWheelerFactory();
const client = new Client(twoWheelerFactory);
```

→ `TwoWheelerFactory.createVehicle()` returns a new `TwoWheeler()` object.
→ `Client` holds it in `this.pVehicle`.

---

### Step 2: Client uses the object

```js
const vehicle = client.getVehicle();
vehicle.printVehicle();
```

→ `printVehicle()` of `TwoWheeler` executes → `"I am two wheeler"` printed.

---

### Step 3: Same for FourWheeler

Another factory is used:

```js
const fourWheelerFactory = new FourWheelerFactory();
const client2 = new Client(fourWheelerFactory);
client2.getVehicle().printVehicle();
```

→ `"I am four wheeler"` printed.

---

## ⚙️ **7. Code Breakdown with Thinking**

### Step 1: Define Common Interface

```js
class Vehicle {
    printVehicle() {
        throw new Error("Must implement in subclass");
    }
}
```

→ Base structure for all vehicles.

---

### Step 2: Concrete Implementations

```js
class TwoWheeler extends Vehicle {
    printVehicle() {
        console.log("I am two wheeler");
    }
}

class FourWheeler extends Vehicle {
    printVehicle() {
        console.log("I am four wheeler");
    }
}
```

→ Each subclass defines its own behavior.

---

### Step 3: Define Factory Interface

```js
class VehicleFactory {
    createVehicle() {
        throw new Error("Must be implemented in subclass");
    }
}
```

→ Blueprint for all factories.

---

### Step 4: Concrete Factories

```js
class TwoWheelerFactory extends VehicleFactory {
    createVehicle() {
        return new TwoWheeler();
    }
}

class FourWheelerFactory extends VehicleFactory {
    createVehicle() {
        return new FourWheeler();
    }
}
```

→ Each knows **how** to create its product.

---

### Step 5: Client

```js
class Client {
    constructor(factory) {
        this.vehicle = factory.createVehicle();
    }

    getVehicle() {
        return this.vehicle;
    }
}
```

→ Client only depends on `VehicleFactory`, not `TwoWheeler` or `FourWheeler`.

---

### Step 6: Execution

```js
const twoFactory = new TwoWheelerFactory();
const client1 = new Client(twoFactory);
client1.getVehicle().printVehicle();

const fourFactory = new FourWheelerFactory();
const client2 = new Client(fourFactory);
client2.getVehicle().printVehicle();
```

---

### ✅ Output

```
I am two wheeler
I am four wheeler
```

---

## 📊 **8. Class Diagram Explanation (Text Representation)**

![](https://media.geeksforgeeks.org/wp-content/uploads/20250923131205175145/factory_method_design_pattern_class_diagram.webp)

```
          ┌────────────────────┐
          │     Vehicle        │  ← Product (Abstract)
          │ + printVehicle()   │
          └────────┬───────────┘
                   │
     ┌─────────────┴──────────────┐
     │                            │
┌─────────────┐           ┌─────────────┐
│ TwoWheeler  │           │ FourWheeler │  ← Concrete Products
└─────────────┘           └─────────────┘


          ┌────────────────────┐
          │  VehicleFactory    │  ← Creator (Abstract)
          │ + createVehicle()  │
          └────────┬───────────┘
                   │
     ┌─────────────┴──────────────┐
     │                            │
┌────────────────────┐   ┌────────────────────┐
│ TwoWheelerFactory  │   │ FourWheelerFactory │  ← Concrete Creators
└────────────────────┘   └────────────────────┘


                 ┌───────────┐
                 │   Client  │
                 │ uses any  │
                 │  factory  │
                 └───────────┘
```

---

## 🌍 **9. Real-World Use Cases**

| Domain       | Example                                      | How Factory Helps                                |
| ------------ | -------------------------------------------- | ------------------------------------------------ |
| Web Browsers | Rendering engine creation (HTML, PDF, Flash) | Selects correct renderer dynamically             |
| Android      | `Activity` creation                          | OS decides what subclass to instantiate          |
| E-Commerce   | Payment gateway selection                    | Creates correct gateway (PayPal, Stripe)         |
| Games        | Spawning enemies/items                       | Factory decides which object to create per level |
| Logging      | Log4j / Winston                              | Creates different log appenders dynamically      |

---

## 🏗️ **10. Mini Example Project Idea (Hands-on Practice)**

### **Project: Notification System**

You have multiple notification types:

* **EmailNotification**
* **SMSNotification**
* **WhatsAppNotification**

Each implements `Notification` interface.
Each has its factory:

* `EmailFactory`
* `SMSFactory`
* `WhatsAppFactory`

Client asks for a notification via the factory — gets the correct one automatically.

---

### **Example Code (Simplified)**

```js
class Notification {
    send() {
        throw new Error("Must implement in subclass");
    }
}

class EmailNotification extends Notification {
    send() {
        console.log("Sending Email...");
    }
}

class SMSNotification extends Notification {
    send() {
        console.log("Sending SMS...");
    }
}

class NotificationFactory {
    createNotification() {}
}

class EmailFactory extends NotificationFactory {
    createNotification() {
        return new EmailNotification();
    }
}

class SMSFactory extends NotificationFactory {
    createNotification() {
        return new SMSNotification();
    }
}

// Client
class Client {
    constructor(factory) {
        this.notification = factory.createNotification();
    }
    execute() {
        this.notification.send();
    }
}

// Usage
new Client(new EmailFactory()).execute();
new Client(new SMSFactory()).execute();
```

✅ **Output:**

```
Sending Email...
Sending SMS...
```

---

## ⚖️ **11. Advantages**

* Loose coupling between client & product
* Easy to add new product types
* Centralized creation logic
* Improves code scalability
* Supports OCP (Open for extension, closed for modification)

---

## ⚠️ **12. Disadvantages**

* Adds extra classes (increased complexity)
* Slightly more code overhead for small systems
* Requires subclassing (in some languages)

---

## 🧩 **13. Summary (Interview View)**

| Aspect                 | Description                                    |
| ---------------------- | ---------------------------------------------- |
| **Pattern Type**       | Creational                                     |
| **Problem Solved**     | Object creation without specifying exact class |
| **Key Principle**      | Encapsulation + Polymorphism                   |
| **Real-World Analogy** | Restaurant kitchen preparing meals             |
| **Design Goal**        | Decouple object creation from usage            |

---