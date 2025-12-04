# **Abstract Factory Pattern**

## **1. Real-World Thinking**

### Problem Scenario (Why we need it)

Imagine you are building a **global car manufacturing system**:

* Cars for **North America**: need **sedan cars** with **left-hand driving**, **airbags**, and specific **safety regulations**.
* Cars for **Europe**: need **hatchbacks** with **right-hand driving**, **fuel efficiency rules**, **emission standards**.
* Cars for **Asia**: different engine types, design, or features.

Now think:

* If we just write `Sedan` or `Hatchback` directly in our client code, it becomes **tightly coupled**.
* Changing requirements for a region means modifying multiple places in the code.
* Adding a new region requires **scattered changes**, introducing **bugs**.

**Problem:** How do we create **families of related objects** (cars, specifications, safety features) for each region **without changing existing code**?

---

## **2. What is Abstract Factory Pattern**

* It is a **creational design pattern**.
* Provides an **interface to create families of related objects** without specifying concrete classes.
* Often called **“Factory of Factories”**.

**Idea:**

* You don’t create cars directly.
* You ask a **factory for a region** (North America Factory), which produces all related objects (Car + Specification).
* **Decouples creation from usage**.

---

## **3. Key Components**

| Component            | Role                                                                                           |
| -------------------- | ---------------------------------------------------------------------------------------------- |
| **Abstract Factory** | Interface for creating a family of related objects (e.g., `CarFactory`).                       |
| **Concrete Factory** | Implements abstract factory for specific product families (e.g., `NorthAmericaCarFactory`).    |
| **Abstract Product** | Interface/type of a product (e.g., `Car`, `CarSpecification`).                                 |
| **Concrete Product** | Actual product implementing the abstract product (e.g., `Sedan`, `NorthAmericaSpecification`). |
| **Client**           | Uses abstract factory to create products, unaware of concrete classes.                         |

---

## **4. How it Solves Problems**

| Problem Without Pattern                                  | Solution With Abstract Factory                              |
| -------------------------------------------------------- | ----------------------------------------------------------- |
| Tightly coupled code to specific products                | Client uses abstract interfaces (`Car`, `CarSpecification`) |
| Adding a new region requires changes everywhere          | Just add a new concrete factory (e.g., `AsiaCarFactory`)    |
| Changes in car specs break code                          | Changes are encapsulated inside the region-specific factory |
| Multiple related objects must be consistent for a family | Factory guarantees objects belong to the same family        |

---

## **5. Real-World Analogies**

1. **Operating Systems UI Theme**:

   * Abstract Factory: `ThemeFactory`
   * Concrete Factories: `WindowsFactory`, `MacFactory`
   * Products: `Button`, `Checkbox`
   * Each factory produces **matching buttons and checkboxes** for a platform.

2. **Cloud Providers**:

   * Abstract Factory: `CloudFactory`
   * Concrete Factories: `AWSFactory`, `AzureFactory`
   * Products: `Storage`, `Compute`
   * Each factory creates objects according to **provider rules**.

---

## **6. Implementation in JavaScript**

![](https://media.geeksforgeeks.org/wp-content/uploads/20240205125205/AbstractFactoryexampledrawio-(1)-2.png)

### **Step 1: Abstract Products**

```javascript
class Car {
    assemble() { throw new Error('Method not implemented'); }
}

class CarSpecification {
    display() { throw new Error('Method not implemented'); }
}
```

### **Step 2: Concrete Products**

```javascript
// Cars
class Sedan extends Car {
    assemble() { console.log("Assembling Sedan car."); }
}

class Hatchback extends Car {
    assemble() { console.log("Assembling Hatchback car."); }
}

// Specifications
class NorthAmericaSpecification extends CarSpecification {
    display() {
        console.log("North America Specification: Safety features compliant.");
    }
}

class EuropeSpecification extends CarSpecification {
    display() {
        console.log("Europe Specification: Fuel efficiency & emissions compliant.");
    }
}
```

### **Step 3: Abstract Factory**

```javascript
class CarFactory {
    createCar() { throw new Error('Not implemented'); }
    createSpecification() { throw new Error('Not implemented'); }
}
```

### **Step 4: Concrete Factories**

```javascript
class NorthAmericaCarFactory extends CarFactory {
    createCar() { return new Sedan(); }
    createSpecification() { return new NorthAmericaSpecification(); }
}

class EuropeCarFactory extends CarFactory {
    createCar() { return new Hatchback(); }
    createSpecification() { return new EuropeSpecification(); }
}
```

### **Step 5: Client Code**

```javascript
const naFactory = new NorthAmericaCarFactory();
let car = naFactory.createCar();
let spec = naFactory.createSpecification();
car.assemble();
spec.display();

const euFactory = new EuropeCarFactory();
car = euFactory.createCar();
spec = euFactory.createSpecification();
car.assemble();
spec.display();
```

**Output:**

```
Assembling Sedan car.
North America Specification: Safety features compliant.
Assembling Hatchback car.
Europe Specification: Fuel efficiency & emissions compliant.
```

---

## **7. Advantages**

1. Decouples **client code** from concrete classes.
2. Ensures **consistency** across a family of related objects.
3. Adding a new family is easy: just create a new **factory**.
4. Encapsulates **object creation logic**.

---

## **8. Disadvantages**

1. Can add **complexity** for simple projects.
2. Adding new **product types** may require changes in all factories.
3. Violates **Open/Closed principle** if not designed carefully.
4. Can lead to **many classes** for larger projects.

---

## **9. When to Use**

* System has **multiple families of related products**.
* You need **interchangeable product families**.
* Want to **encapsulate creation logic**.
* Need **flexibility and scalability**.

---

## **10. When Not to Use**

* Only **single products** required.
* Families are **unlikely to change**.
* Overhead of multiple factories outweighs benefits.
* Simpler patterns (Factory Method or Builder) are sufficient.

---

## ✅ **Key Takeaways**

1. Abstract Factory = **Factory of Factories**.
2. Ensures **loose coupling**.
3. Helps in **maintaining consistency** for a family of objects.
4. Adds **scalability and flexibility** for future changes.
5. Can be overkill for **small or static systems**.

---
