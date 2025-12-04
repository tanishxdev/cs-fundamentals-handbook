// ===================================================================
//       OOP Concepts in JavaScript (Simplified Demo)
// ===================================================================
// Covers all major OOP pillars in one file:
// 1️⃣ Classes & Objects
// 2️⃣ Encapsulation
// 3️⃣ Abstraction
// 4️⃣ Inheritance
// 5️⃣ Polymorphism
// ===================================================================

// ------------------------------------------------------------
// 1️⃣ CLASSES & OBJECTS
// ------------------------------------------------------------
console.log("\n ⭐ Classes and Objects in OOP");

// Class definition
class Student {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    // Method 1
    takeExam() {
        console.log(`${this.name} is taking an exam.`);
    }

    // Method 2
    takeLeave() {
        console.log(`${this.name} is taking leave.`);
    }
}

// Object instantiation
const studentA = new Student("Alice", 20);
studentA.takeExam();
studentA.takeLeave();

const studentB = new Student("Bob", 22);
studentB.takeExam();
studentB.takeLeave();


// ------------------------------------------------------------
// 2️⃣ ENCAPSULATION — Hiding Data with Getters & Setters
// ------------------------------------------------------------
console.log("\n ⭐ Encapsulation in OOP");

class Employee {
    constructor() {
        this.id = null;
        this.name = null;
    }

    // Setters — control how data is assigned
    setId(id) {
        this.id = id;
    }

    setName(name) {
        this.name = name;
    }

    // Getters — controlled access to data
    getId() {
        return this.id;
    }

    getName() {
        return this.name;
    }
}

// Object creation
const emp = new Employee();
emp.setId(101);
emp.setName('Geek');

// Accessing via getters
console.log('Employee ID: ' + emp.getId());
console.log('Employee Name: ' + emp.getName());


// ------------------------------------------------------------
// 3️⃣ ABSTRACTION — Hiding Implementation Details
// ------------------------------------------------------------
console.log("\n ⭐ Abstraction in OOP");

// Abstract base class
class Vehicle {
    constructor() {
        if (this.constructor === Vehicle) {
            throw new Error("Abstract classes can't be instantiated directly.");
        }
    }

    // Abstract method (must be implemented by subclasses)
    accelerate() {
        throw new Error("Method 'accelerate()' must be implemented.");
    }

    // Concrete method — common for all
    brake() {
        console.log("The vehicle is braking.");
    }

    startEngine() {
        console.log("The engine has started.");
    }
}

// Derived class implementing abstract methods
class Car extends Vehicle {
    accelerate() {
        console.log("The car is accelerating.");
    }

    brake() {
        console.log("The car is braking.");
    }
}

// Using abstraction
const myCar = new Car();
myCar.startEngine();
myCar.accelerate();
myCar.brake();


// ------------------------------------------------------------
// 4️⃣ INHERITANCE — Reusing Parent Functionality
// ------------------------------------------------------------
console.log("\n ⭐ Inheritance in OOP");

// Parent class
class Animal {
    eat() {
        console.log('Animal is eating...');
    }

    sleep() {
        console.log('Animal is sleeping...');
    }
}

// Child class inheriting from parent
class Dog extends Animal {
    bark() {
        console.log('Dog is barking!');
    }
}

// Using inheritance
const myDog = new Dog();
myDog.eat();    // Inherited method
myDog.sleep();  // Inherited method
myDog.bark();   // Child-specific method


// ------------------------------------------------------------
// 5️⃣ POLYMORPHISM — Same Method, Different Behavior
// ------------------------------------------------------------
console.log("\n ⭐ Polymorphism in OOP");

class Calculator {
    // Overloaded-like behavior using argument checks
    add(a, b, c) {
        if (arguments.length === 2) {
            return a + b; // Two-parameter version
        } else if (arguments.length === 3) {
            return a + b + c; // Three-parameter version
        }
    }
}

// Using polymorphism
const calc = new Calculator();
console.log('Sum of 5 and 3:', calc.add(5, 3));
console.log('Sum of 4, 6, and 2:', calc.add(4, 6, 2));


// ===================================================================
// ✅ OUTPUT SUMMARY (Concept Recap)
// ===================================================================
//
// \n ⭐ Classes & Objects
//   - Created Student class and used multiple objects
//
// \n ⭐ Encapsulation
//   - Used private data with getter/setter methods
//
// \n ⭐ Abstraction
//   - Defined abstract Vehicle class and implemented in Car
//
// \n ⭐ Inheritance
//   - Dog inherited behaviors from Animal
//
// \n ⭐ Polymorphism
//   - Same `add()` behaves differently depending on arguments
//
// ===================================================================
// This demonstrates all OOP concepts using clean, modular JavaScript.
// ===================================================================
