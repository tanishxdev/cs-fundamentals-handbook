# Design Patterns 

## What are Design Patterns?

* **Reusable solutions** to common software design problems.
* They’re **templates/blueprints**, not finished code.
* Help make code **cleaner, more maintainable, scalable, and flexible**.
* Provide a **shared vocabulary** among developers.

---

## Why Learn Them?

* Avoid reinventing the wheel.
* Apply tried & tested solutions.
* Write **modular, extensible, and reusable** code.
* Faster development & easier maintenance.

---

## Types of Design Patterns

Design patterns are broadly divided into **3 categories**:

---

### 1️⃣ Creational Patterns → *How objects are created*

Focus: Object creation while hiding complexities.

* **Factory Method** → Creates objects without specifying the exact class.
  Example: `ShapeFactory` that returns Circle, Square, etc.
* **Abstract Factory** → Creates families of related objects.
  Example: UI Toolkit with `Button` + `Checkbox` (Windows, Mac versions).
* **Singleton** → Ensures only one instance of a class exists.
  Example: Logger, Database connection.
* **Prototype** → Clone an existing object instead of creating from scratch.
  Example: Cloning a configured object.
* **Builder** → Step-by-step construction of complex objects.
  Example: Building a `House` (walls, roof, garden separately).

---

### 2️⃣ Structural Patterns → *How objects/classes are composed*

Focus: Relationships between objects, making them work together.

* **Adapter** → Converts one interface into another.
  Example: Phone charger adapter.
* **Bridge** → Separates abstraction from implementation.
  Example: Remote control (abstraction) + TV (implementation).
* **Composite** → Tree structures treating group & individual objects uniformly.
  Example: File system (files + folders).
* **Decorator** → Add responsibilities dynamically without changing the class.
  Example: Adding scroll bar to a window UI.
* **Facade** → Simplified interface to a complex subsystem.
  Example: `Computer.start()` internally calls CPU, Memory, Disk setup.
* **Flyweight** → Reuse shared objects to save memory.
  Example: Characters in a text editor.
* **Proxy** → Placeholder controlling access to another object.
  Example: Virtual proxy for large images (lazy loading).

---

### 3️⃣ Behavioral Patterns → *How objects communicate*

Focus: Interaction, responsibility assignment, control flow.

* **Chain of Responsibility** → Pass request through chain until handled.
  Example: Support system (Level 1 → Level 2 → Manager).
* **Command** → Encapsulate a request as an object.
  Example: Undo/Redo system.
* **Interpreter** → Define grammar & interpret language.
  Example: Regex engine, calculators.
* **Mediator** → Central object manages communication between objects.
  Example: Chatroom mediator between users.
* **Memento** → Capture/restore object state.
  Example: Save game functionality.
* **Observer** → One-to-many dependency, notify on change.
  Example: YouTube channel subscribers.
* **State** → Object changes behavior based on state.
  Example: Traffic light system.
* **Strategy** → Switch algorithms at runtime.
  Example: Payment strategy (UPI, Card, Netbanking).
* **Template Method** → Define algorithm structure, subclasses fill steps.
  Example: Cooking recipe template.
* **Visitor** → Separate algorithms from object structure.
  Example: Tax calculation for different products.

---

## 🏆 Quick Analogy to Remember

* **Creational** = *"How to create objects?"*
* **Structural** = *"How to organize objects?"*
* **Behavioral** = *"How objects talk to each other?"*

