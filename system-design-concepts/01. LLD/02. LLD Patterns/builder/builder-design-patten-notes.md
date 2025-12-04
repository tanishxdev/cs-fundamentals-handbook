# Builder System Design

## **1. Understanding the Problem (Real World Thinking)**

Imagine you want to build **custom computers** for different purposes: gaming, office work, or design.

* Each computer has **CPU, RAM, storage, GPU**.
* Different variations require different combinations.

**Challenges if we just use a normal constructor:**

1. Constructors get very long (telescoping constructors problem).

   ```js
   new Computer("i7", "16GB", "1TB SSD", "RTX 4070");
   ```

   * Hard to remember parameter order.
   * Hard to manage optional parts.

2. Every small change in construction logic may break client code.

3. We want **flexibility**, **reusability**, and **step-by-step construction**.

---

## **2. Solution: Builder Design Pattern**

**Idea:** Separate **construction logic** from the final product representation.

* Use a **Builder** class to construct the product step by step.
* Optionally, use a **Director** to control construction order.
* Client just tells the builder what parts to include.

**Analogy:**

* Think of **ordering a custom pizza**:

  * Pizza = Product
  * PizzaBuilder = Builder class to add cheese, toppings, crust
  * Chef = Director who follows a recipe (optional)
  * Customer = Client

---

## **3. Components of Builder Pattern**

| Component           | Role                                                                                 |
| ------------------- | ------------------------------------------------------------------------------------ |
| **Product**         | Final object being constructed (e.g., `Computer`)                                    |
| **Builder**         | Interface or abstract class specifying steps (e.g., `buildCPU()`)                    |
| **ConcreteBuilder** | Implements builder to create specific representation (e.g., `GamingComputerBuilder`) |
| **Director**        | Controls construction order (optional)                                               |
| **Client**          | Uses builder (and director) to create product                                        |

---

## **4. Step-by-Step Implementation**

![](https://media.geeksforgeeks.org/wp-content/uploads/20240206185827/UML-Class-Diagram-for-Builder-Design-Pattern.webp)

### **Step 1: Product Class**

```js
class Computer {
    constructor() {
        this.cpu = null;
        this.ram = null;
        this.storage = null;
        this.gpu = null;
    }

    setCPU(cpu) { this.cpu = cpu; }
    setRAM(ram) { this.ram = ram; }
    setStorage(storage) { this.storage = storage; }
    setGPU(gpu) { this.gpu = gpu; }

    displayInfo() {
        console.log(`Computer Configuration:
CPU: ${this.cpu}
RAM: ${this.ram}
Storage: ${this.storage}
GPU: ${this.gpu}\n`);
    }
}
```

---

### **Step 2: Builder Interface**

```js
class Builder {
    buildCPU() {}
    buildRAM() {}
    buildStorage() {}
    buildGPU() {}
    getResult() {}
}
```

---

### **Step 3: ConcreteBuilder**

```js
class GamingComputerBuilder extends Builder {
    constructor() {
        super();
        this.computer = new Computer();
    }

    buildCPU() { this.computer.setCPU("i7 14HX"); }
    buildRAM() { this.computer.setRAM("32GB DDR5"); }
    buildStorage() { this.computer.setStorage("2TB NVMe SSD"); }
    buildGPU() { this.computer.setGPU("RTX 4070"); }

    getResult() { return this.computer; }
}
```

---

### **Step 4: Director (Optional)**

```js
class Director {
    construct(builder) {
        builder.buildCPU();
        builder.buildRAM();
        builder.buildStorage();
        builder.buildGPU();
    }
}
```

---

### **Step 5: Client Usage**

```js
const gamingBuilder = new GamingComputerBuilder();
const director = new Director();

director.construct(gamingBuilder); // Director controls building process
const gamingComputer = gamingBuilder.getResult();

gamingComputer.displayInfo();
```

**Output:**

```
Computer Configuration:
CPU: i7 14HX
RAM: 32GB DDR5
Storage: 2TB NVMe SSD
GPU: RTX 4070
```

---

## **5. Why This Is Useful**

1. **Step-by-step construction**

   * Flexible and readable.

2. **Different representations**

   * GamingComputerBuilder, OfficeComputerBuilder, etc.

3. **Avoids long constructors**

   * Optional parts can be skipped easily.

4. **Immutable objects**

   * You can design builder to produce objects that cannot be modified later.

---

## **6. Pros and Cons**

**Pros:**

* Flexible object creation.
* Clear separation of construction and representation.
* Supports different variations without breaking client code.

**Cons:**

* Requires a new ConcreteBuilder for each representation.
* Slightly more complex code for simple objects.
* May overkill for simple products.

---

## **7. Advanced Tips / Real-World Extensions**

1. **Fluent API (Method Chaining)**:

```js
class ComputerBuilder {
    constructor() { this.computer = new Computer(); }
    setCPU(cpu) { this.computer.setCPU(cpu); return this; }
    setRAM(ram) { this.computer.setRAM(ram); return this; }
    setStorage(storage) { this.computer.setStorage(storage); return this; }
    setGPU(gpu) { this.computer.setGPU(gpu); return this; }
    build() { return this.computer; }
}

const customComputer = new ComputerBuilder()
    .setCPU("i5")
    .setRAM("16GB")
    .setStorage("1TB HDD")
    .setGPU("GTX 1650")
    .build();
```

2. **Optional Director**

   * Director is useful when you have **standard construction sequences**.
   * For completely custom builds, client can skip Director.

3. **Immutable Products**

   * Once built, prevent modification of the product.
   * Useful in thread-safe or configuration-sensitive systems.

---

✅ **Key Takeaway:**

Builder pattern = **flexible, step-by-step object construction**, perfect for complex products with multiple configurations.

* Think: **Custom Pizza / Computer / Document / UI Component Builder**.
* Always separate **construction logic** from the **final product representation**.