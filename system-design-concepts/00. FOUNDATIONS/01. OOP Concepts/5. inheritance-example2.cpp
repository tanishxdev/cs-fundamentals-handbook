#include <bits/stdc++.h>
using namespace std;
/**
👉 Concept

**Inheritance** allows classes to build upon other classes — 
sharing attributes and behaviors while extending or customizing functionality.

There are multiple types of inheritance in C++:
- **Single Inheritance** → One base, one derived
- **Multi-Level Inheritance** → Derived class acts as base for another
- **Hierarchical Inheritance** → Multiple classes inherit from one base
- **Multiple Inheritance** → One class inherits from multiple bases (rare, used carefully)

👉 Why Complex Inheritance is Needed

| Without Inheritance | With Inheritance |
| -------------------- | ---------------- |
| Every entity redefines common data like `name`, `age`. | Base class (Person) stores and manages common properties. |
| No hierarchy or real-world modeling. | Models real organization hierarchy cleanly. |
| Code duplication and poor scalability. | Centralized logic and extensibility. |

👉 Real-life Analogy

In a company:
- A **Person** has basic info (name, age).  
- An **Employee** is a Person with an ID and salary.  
- A **Manager** is an Employee with a team and reporting functions.

👉 Problem Statement

Design a system to represent a company’s employee hierarchy:
1. Base class `Person` — defines name and age.
2. Derived class `Employee` — adds ID and salary.
3. Derived class `Manager` — adds management behavior (team and reports).
4. Demonstrate **multi-level inheritance** and **method overriding**.
*/

/*
------------------------------------------------------------
Problem: Complex Inheritance — Company Employee Hierarchy
------------------------------------------------------------
Goal:
1. Show reusability through multiple inheritance levels.
2. Implement hierarchical behavior between Person → Employee → Manager.
3. Demonstrate base, derived, and overridden functions.
------------------------------------------------------------
*/

// ----------------------------------------------------------
// BASE CLASS: Person
// Common attributes for all people
// ----------------------------------------------------------
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Employee (inherits from Person)
// Adds work-related attributes
// ----------------------------------------------------------
class Employee : public Person {
protected:
    int empId;
    double salary;

public:
    Employee(string n, int a, int id, double s)
        : Person(n, a), empId(id), salary(s) {}

    void displayDetails() override {
        cout << "Employee ID: " << empId << " | Name: " << name
             << " | Age: " << age << " | Salary: Rs. " << salary << endl;
    }

    void work() {
        cout << name << " is working on assigned tasks." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Manager (inherits from Employee)
// Adds managerial responsibilities
// ----------------------------------------------------------
class Manager : public Employee {
private:
    vector<string> teamMembers;

public:
    Manager(string n, int a, int id, double s)
        : Employee(n, a, id, s) {}

    void addTeamMember(string memberName) {
        teamMembers.push_back(memberName);
    }

    void displayTeam() {
        cout << "Manager " << name << "'s Team: ";
        if (teamMembers.empty()) {
            cout << "No team members yet." << endl;
        } else {
            for (auto &m : teamMembers)
                cout << m << " ";
            cout << endl;
        }
    }

    // Method overriding — custom display for manager
    void displayDetails() override {
        cout << "[Manager Profile]" << endl;
        cout << "ID: " << empId << " | Name: " << name << " | Age: " << age
             << " | Salary: Rs. " << salary << endl;
        displayTeam();
    }

    void conductMeeting() {
        cout << name << " is conducting a team meeting." << endl;
    }
};

// ----------------------------------------------------------
// DERIVED CLASS: Intern (inherits from Employee)
// Represents entry-level role (hierarchical inheritance)
// ----------------------------------------------------------
class Intern : public Employee {
public:
    Intern(string n, int a, int id, double s)
        : Employee(n, a, id, s) {}

    void learn() {
        cout << name << " is learning new technologies." << endl;
    }

    // Optional override — simpler display
    void displayDetails() override {
        cout << "[Intern]" << endl;
        cout << "ID: " << empId << " | Name: " << name
             << " | Age: " << age << " | Stipend: Rs. " << salary << endl;
    }
};

// ----------------------------------------------------------
// main() — Demonstrates Complex Inheritance
// ----------------------------------------------------------
int main() {
    // Manager Object (Multi-level inheritance)
    Manager m1("Alice Johnson", 40, 101, 90000);
    m1.addTeamMember("Bob");
    m1.addTeamMember("Charlie");
    m1.displayDetails();
    m1.conductMeeting();

    cout << "----------------------------------------" << endl;

    // Employee Object
    Employee e1("David", 30, 201, 60000);
    e1.displayDetails();
    e1.work();

    cout << "----------------------------------------" << endl;

    // Intern Object (Hierarchical inheritance)
    Intern i1("Eva", 22, 301, 15000);
    i1.displayDetails();
    i1.learn();

    return 0;
}

/*
👉 Step-by-Step Flow

1. `Person` defines basic data (name, age).
2. `Employee` extends `Person` → adds ID and salary.
3. `Manager` extends `Employee` → adds team management features.
4. `Intern` also extends `Employee` → demonstrates hierarchical inheritance.
5. Each level reuses and extends functionality logically.

👉 Example Output

[Manager Profile]
ID: 101 | Name: Alice Johnson | Age: 40 | Salary: Rs. 90000
Manager Alice Johnson's Team: Bob Charlie
Alice Johnson is conducting a team meeting.
----------------------------------------
Employee ID: 201 | Name: David | Age: 30 | Salary: Rs. 60000
David is working on assigned tasks.
----------------------------------------
[Intern]
ID: 301 | Name: Eva | Age: 22 | Stipend: Rs. 15000
Eva is learning new technologies.

👉 Key Takeaways

| Concept | Description |
| -------- | ------------ |
| **Multi-Level Inheritance** | A derived class becomes the base for another (Person → Employee → Manager). |
| **Hierarchical Inheritance** | Multiple derived classes (Manager, Intern) from a single base (Employee). |
| **Method Overriding** | Derived classes redefine base methods (e.g., `displayDetails()`). |
| **Code Reusability** | Shared logic across all employee types — fewer bugs and cleaner design. |

👉 How Inheritance Helps in System Design

In real-world system design:
- **Base classes** define common rules (e.g., User, Product, Vehicle).
- **Derived classes** specialize behavior (e.g., AdminUser, PremiumProduct, ElectricVehicle).
- Promotes **DRY (Don’t Repeat Yourself)** principle.
- Enables **hierarchical modeling** — a key aspect of Object-Oriented System Design.

**Example (System Design analogy):**
- Base Interface → `PaymentGateway`
- Derived → `Razorpay`, `Stripe`, `PayPal`
- Business logic → works only on `PaymentGateway*` → clean abstraction & inheritance combo.

👉 Next Step

Next, we’ll combine inheritance + abstraction → **Polymorphism**  
to demonstrate how a **single interface can represent multiple behaviors dynamically.**
*/
