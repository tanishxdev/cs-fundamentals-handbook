
##  **CREATIONAL DESIGN PATTERNS (Object Creation Patterns)**

| Pattern              | Real-World Analogy                                        | Core Purpose                                | When to Use                                       | Example Use Case                     |
| -------------------- | --------------------------------------------------------- | ------------------------------------------- | ------------------------------------------------- | ------------------------------------ |
| **Singleton**        | One CEO managing entire company                           | Ensure only one instance exists             | Logging, Config, DB connection                    | Logger, AppConfig                    |
| **Factory Method**   | Restaurant kitchen decides which chef cooks               | Delegate object creation to subclasses      | When you don’t know which subclass to instantiate | NotificationFactory (SMS/Email)      |
| **Abstract Factory** | Furniture Factory — produces chairs & tables of one style | Create families of related objects          | Multiple factories with consistent themes         | GUI toolkit (Windows/Mac UI)         |
| **Builder**          | House Construction — floor, walls, roof step-by-step      | Construct complex objects step-by-step      | When object construction is complex               | HouseBuilder, CarBuilder             |
| **Prototype**        | Copying document templates                                | Clone existing object instead of recreating | When creating objects is costly                   | Shape.clone(), GameCharacter.clone() |

---

##  **STRUCTURAL DESIGN PATTERNS (Object Composition Patterns)**

| Pattern       | Real-World Analogy                   | Core Purpose                                         | When to Use                                                      | Example Use Case                         |
| ------------- | ------------------------------------ | ---------------------------------------------------- | ---------------------------------------------------------------- | ---------------------------------------- |
| **Adapter**   | Universal plug adapter               | Make incompatible interfaces work together           | Integrating legacy APIs                                          | New Payment System with old Gateway      |
| **Bridge**    | Remote control → TV                  | Decouple abstraction from implementation             | When both interface and implementation should vary independently | Shapes + Colors system                   |
| **Composite** | File system (Folder + File)          | Treat group of objects like a single object          | Hierarchical structures                                          | File Explorer, Organization Tree         |
| **Decorator** | Add toppings to a pizza              | Add responsibilities dynamically without subclassing | When you need flexible feature addition                          | Coffee cost calculator with add-ons      |
| **Facade**    | Hotel Reception Desk                 | Simplify complex subsystems with one interface       | Provide simple API for complex system                            | HomeTheaterFacade controlling subsystems |
| **Flyweight** | Text editor characters sharing fonts | Reuse heavy shared data efficiently                  | Millions of similar objects                                      | GUI icons, game trees                    |
| **Proxy**     | Security guard controlling access    | Control access to another object                     | Add access control, caching, or lazy loading                     | Virtual proxy, DB proxy, API gateway     |

---

##  **BEHAVIORAL DESIGN PATTERNS (Communication / Control Patterns)**

| Pattern                     | Real-World Analogy                          | Core Purpose                                            | When to Use                                 | Example Use Case                      |
| --------------------------- | ------------------------------------------- | ------------------------------------------------------- | ------------------------------------------- | ------------------------------------- |
| **Chain of Responsibility** | Customer support escalation                 | Pass request along chain until handled                  | Multiple handlers may process a request     | Support ticket, logging filters       |
| **Command**                 | Remote control with buttons                 | Encapsulate request as object                           | Undo/Redo, task queues                      | Text Editor, Smart Home               |
| **Interpreter**             | Grammar or expression parser                | Interpret expressions or rules                          | Define language grammar or conditions       | Math expression evaluator             |
| **Iterator**                | Music playlist or remote control next/prev  | Sequentially access elements without exposing structure | Collection traversal                        | Music player, Employee list iterator  |
| **Mediator**                | Air traffic control tower                   | Centralize communication between multiple objects       | Reduce direct dependencies                  | ChatRoom, Air Traffic System          |
| **Memento**                 | Game save or undo feature                   | Capture & restore object state                          | Need rollback or history                    | Text editor undo, game save state     |
| **Observer**                | YouTube subscribers notification            | One-to-many update dependency                           | Publish-subscribe model                     | Weather station, Stock notifier       |
| **State**                   | ATM Machine behavior per state              | Change behavior based on internal state                 | State-specific logic variations             | Media player, Traffic signal          |
| **Strategy**                | Payment via different methods               | Choose algorithm dynamically                            | Multiple interchangeable behaviors          | Sorting, Compression, Payment system  |
| **Template Method**         | Coffee machine steps (boil → brew → pour)   | Define skeleton; let subclass override steps            | Common algorithm with variations            | Beverage preparation, file processing |
| **Visitor**                 | Tax inspector visiting different businesses | Separate algorithm from object structure                | When new operations need to be added easily | Shopping cart, Banking accounts       |

---

##  **Similar Patterns — Key Differences**

| Confusing Pair                  | Difference                                                                                    |
| ------------------------------- | --------------------------------------------------------------------------------------------- |
| **Factory vs Abstract Factory** | Factory → creates one product; Abstract Factory → creates related families of products        |
| **Factory vs Builder**          | Factory → returns ready-made object; Builder → step-by-step construction                      |
| **Prototype vs Factory**        | Prototype → clones existing; Factory → creates new                                            |
| **Decorator vs Proxy**          | Decorator → adds new behavior; Proxy → controls access                                        |
| **Adapter vs Bridge**           | Adapter → works with incompatible interfaces; Bridge → separates abstraction & implementation |
| **State vs Strategy**           | State → internal object condition change; Strategy → algorithm chosen externally              |
| **Memento vs Command**          | Memento → saves state; Command → performs & can undo actions                                  |
| **Observer vs Mediator**        | Observer → broadcast updates; Mediator → central coordinator                                  |

---

##  **How to Choose the Right Pattern**

| **If You Want To...**             | **Think Of Pattern**          | **Why**                                 |
| --------------------------------- | ----------------------------- | --------------------------------------- |
| Avoid creating duplicate objects  | Prototype / Flyweight         | Clone or share instances                |
| Manage object lifecycle cleanly   | Factory / Builder / Singleton | Decouple creation logic                 |
| Extend functionality dynamically  | Decorator                     | Add behaviors at runtime                |
| Reuse shared state                | Flyweight                     | Memory optimization                     |
| Simplify a subsystem              | Facade                        | Single entry point                      |
| Integrate incompatible interfaces | Adapter                       | Interface conversion                    |
| Handle dynamic commands or undo   | Command / Memento             | Encapsulated actions                    |
| Broadcast updates                 | Observer                      | Pub-sub mechanism                       |
| Switch behavior dynamically       | State / Strategy              | Context-based or algorithm-based change |
| Traverse a collection             | Iterator                      | Unified traversal                       |
| Execute grammar or logic          | Interpreter                   | Rule evaluation                         |
| Coordinate complex interactions   | Mediator                      | Centralized communication               |

---

##  **Summary Cheat Sheet (Condensed View)**

| Category   | Pattern                 | Analogy             | Problem Solved                        |
| ---------- | ----------------------- | ------------------- | ------------------------------------- |
| Creational | Singleton               | One CEO             | Single instance                       |
| Creational | Factory                 | Factory line        | Object creation delegation            |
| Creational | Abstract Factory        | Brand theme factory | Related product families              |
| Creational | Builder                 | House Construction  | Stepwise creation                     |
| Creational | Prototype               | Document Template   | Clone existing                        |
| Structural | Adapter                 | Plug Adapter        | Incompatible interface                |
| Structural | Bridge                  | Remote & TV         | Decouple abstraction & implementation |
| Structural | Composite               | File System         | Tree hierarchy                        |
| Structural | Decorator               | Pizza toppings      | Add behavior dynamically              |
| Structural | Facade                  | Hotel Reception     | Simplify subsystems                   |
| Structural | Flyweight               | Character rendering | Memory optimization                   |
| Structural | Proxy                   | Security guard      | Access control                        |
| Behavioral | Chain of Responsibility | Support escalation  | Sequential handling                   |
| Behavioral | Command                 | Remote Control      | Encapsulate request                   |
| Behavioral | Interpreter             | Grammar parser      | Interpret expressions                 |
| Behavioral | Iterator                | Playlist            | Sequential access                     |
| Behavioral | Mediator                | ATC Tower           | Central communication                 |
| Behavioral | Memento                 | Game Save           | State rollback                        |
| Behavioral | Observer                | YouTube Channel     | Notify subscribers                    |
| Behavioral | State                   | ATM Mode            | Behavior per state                    |
| Behavioral | Strategy                | Payment Choice      | Dynamic algorithm                     |
| Behavioral | Template Method         | Coffee steps        | Algorithm skeleton                    |
| Behavioral | Visitor                 | Tax inspection      | Separate operations                   |

---

##  **Final Thought**

> Design Patterns are **not rules**, they’re **tools**.
> You pick the one that best matches your problem’s **intent**, not just its structure.

If you’re ever confused:

1. Ask: “What problem am I solving?”
2. Identify: “Is it about creation, structure, or behavior?”
3. Then pick from that category using the cheat table above.

---
