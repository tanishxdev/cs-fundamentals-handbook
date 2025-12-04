# What is **Generalization**?
![Generalization](https://media.geeksforgeeks.org/wp-content/uploads/20250829154515190445/generalization.webp)
* **Definition**: Generalization is the process of **extracting shared characteristics (attributes + behaviors)** of multiple classes into a **base class**.

* This represents an **“is-a” relationship**.

* Example:

  * A `SavingsAccount` **is a** `BankAccount`.
  * A `Dog` **is a** `Animal`.

* **UML Notation**:

  * Solid line with **hollow triangle** pointing **from subclass → superclass**.

```
SavingsAccount ───▷ BankAccount
CurrentAccount ───▷ BankAccount
CreditAccount  ───▷ BankAccount
```

---

# 📝 Example 1: Bank Accounts (Basic)

```cpp
#include <iostream>
using namespace std;

// Generalized class (Superclass)
class BankAccount {
public:
    virtual void accountType() {   // virtual → enables polymorphism
        cout << "This is a general bank account" << endl;
    }
};

// Specialized classes (Subclasses)
class SavingsAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a savings account" << endl;
    }
};

class CurrentAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a current account" << endl;
    }
};

class CreditAccount : public BankAccount {
public:
    void accountType() override {
        cout << "This is a credit account" << endl;
    }
};

int main() {
    // Polymorphic behavior
    BankAccount* b1 = new SavingsAccount();
    BankAccount* b2 = new CurrentAccount();
    BankAccount* b3 = new CreditAccount();

    b1->accountType();  // Savings
    b2->accountType();  // Current
    b3->accountType();  // Credit

    delete b1; delete b2; delete b3;
    return 0;
}
```

### ✅ Output

```
This is a savings account
This is a current account
This is a credit account
```

---

# 🟡 Why is this **Generalization**?

* `BankAccount` = **general (abstract) concept**.
* `SavingsAccount`, `CurrentAccount`, `CreditAccount` = **specializations**.
* All subclasses share the **common interface** (accountType), but provide **their own implementation**.
* This avoids **redundancy** and supports **reusability**.

---

# 🧠 Example 2: Animals (Classic Case)

```
      Animal
       ▲
 ┌─────┼─────┐
 Dog   Cat   Bird
```

### C++ Code

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() { cout << "Some generic animal sound\n"; }
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() override { cout << "Meow Meow!\n"; }
};

class Bird : public Animal {
public:
    void speak() override { cout << "Chirp Chirp!\n"; }
};

int main() {
    Animal* a1 = new Dog();
    Animal* a2 = new Cat();
    Animal* a3 = new Bird();

    a1->speak();  // Dog sound
    a2->speak();  // Cat sound
    a3->speak();  // Bird sound

    delete a1; delete a2; delete a3;
}
```

✅ Output:

```
Woof Woof!
Meow Meow!
Chirp Chirp!
```

---

# 🔴 Generalization vs Composition (Quick Recap)

| Feature  | **Generalization**          | **Composition**      |
| -------- | --------------------------- | -------------------- |
| Relation | “**is-a**”                  | “**has-a**”          |
| Lifetime | Child independent of parent | Part dies with whole |
| UML      | Hollow triangle             | Solid diamond        |

Example:

* **Generalization**: A `Dog` is an `Animal`.
* **Composition**: A `House` has `Rooms`.

---

# 🎯 Takeaways

* **Generalization = Inheritance** in OOP.
* Used when different classes share **common structure/behavior**.
* UML: Hollow triangle pointing to **parent**.
* Encourages **reusability** + **polymorphism**.
