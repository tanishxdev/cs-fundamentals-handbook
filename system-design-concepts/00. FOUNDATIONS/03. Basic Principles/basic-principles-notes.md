# Principle

# 🔥 DRY Principle (Don’t Repeat Yourself)

## 1. **Definition (Simple Words)**

👉 DRY ka matlab hai: **“Apna code bar-bar mat likho.”**

* Agar ek logic multiple jagah repeat ho raha hai → usko ek jagah define karo, baaki jagah use karo.
* Repeat karne se:

  * Error chances badh jaate hain
  * Update karna mushkil hota hai
  * Code readability kharab hoti hai

---

## 2. **Real Life Example**

⚡ Socho ek restaurant hai jisme **biryani banane ka recipe** hai.

❌ **Without DRY:**

* Har cook apni copy likhta hai recipe ki (50 copies ban gayi).
* Agar tumne ek ingredient change karna ho → sab 50 copies update karni padengi.

✅ **With DRY:**

* Ek **master recipe book** hai.
* Har cook usi ek recipe book se biryani banata hai.
* Agar ingredient update karna ho → bas ek hi jagah update karna hoga.

---

## 3. **Code Example**

### ❌ Without DRY

```cpp
#include <iostream>
#include <string>
using namespace std;

bool loginUser(string email, string password) {
    // Email validation code repeated
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User logged in successfully." << endl;
    return true;
}

bool registerUser(string email, string password) {
    // Same email validation code repeated again ❌
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User registered successfully." << endl;
    return true;
}

int main() {
    loginUser("sid@abc.com", "1234");
    registerUser("hazra.com", "5678");
    return 0;
}
```

👉 Problem:

* Email validation code dono function me repeat ho gaya hai.
* Agar kal tumhe email validation rule change karna ho (e.g. must contain `.com`) → dono jagah update karna padega.

---

### ✅ With DRY

```cpp
#include <iostream>
#include <string>
using namespace std;

// Common reusable function (Single source of truth)
bool validateEmail(const string& email) {
    if (email.find("@") == string::npos || email.find(".") == string::npos) {
        return false;
    }
    return true;
}

bool loginUser(string email, string password) {
    if (!validateEmail(email)) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User logged in successfully." << endl;
    return true;
}

bool registerUser(string email, string password) {
    if (!validateEmail(email)) {
        cout << "Invalid email!" << endl;
        return false;
    }
    cout << "User registered successfully." << endl;
    return true;
}

int main() {
    loginUser("sid@abc.com", "1234");
    registerUser("hazra.com", "5678");
    return 0;
}
```

👉 Ab:

* Email validation ek hi jagah likha hai → `validateEmail()`
* Agar rule badalna ho → bas ek function update karo.

---

## 4. **Why DRY is Important?**

* ✅ **Code reusability** → ek jagah likho, har jagah use karo.
* ✅ **Maintenance easy** → ek change = har jagah update ho gaya.
* ✅ **Less bugs** → copy-paste mistakes avoid.
* ✅ **Readable** → developer ko bar-bar same code padhna nahi padta.
* ✅ **Consistency** → sab jagah same logic chalega.

---

## 5. **DRY in Real Software Projects**

* 🏦 **Banking App:** Balance calculation bar-bar likhne ke bajaye ek `calculateBalance()` method.
* 🛒 **E-Commerce:** Discount rule ek jagah define ho, cart, checkout, invoice sab me wahi call ho.
* 🎵 **Music App:** `playSong()` logic ek hi jagah ho, chahe playlist se play ho ya search se.

---

## 6. **Approaches to Apply DRY**

1. **Functions** → common logic ko ek function me likho.
2. **Classes & Inheritance** → common functionality ko base class me rakho.
3. **Constants/Config** → magic numbers repeat mat karo, ek const define karo.
4. **Modules/Packages** → reusable code ko library/module me rakho.

---

## 7. **Key Takeaway**

👉 **DRY Principle = Don’t Repeat Yourself.**
Ek jagah likho, har jagah use karo. Isse:

* code short, clean, consistent hota hai
* maintenance easy hota hai
* bugs kam hote hain


---

# 🎯 KISS Principle (Keep It Simple, Stupid)


## 1. **Definition (Simple Words)**

👉 **KISS principle ka matlab hai: “Code aur design ko unnecessarily complex mat banao, jitna simple ho sake utna rakho.”**

* Simple solutions: samajhna easy, implement karna easy, maintain karna easy.
* Complex solutions: zyada bugs, zyada time, maintenance problem.

---

## 2. **Real Life Example**

⚡ **Without KISS**
Socho tum ek **TV remote** banate ho.
Aur usme 200 buttons daal dete ho (sab features ek hi remote me).
👉 User confuse ho jaata hai, simple task bhi mushkil ho jaata hai.

⚡ **With KISS**
TV remote me **basic buttons hi hote hain** (Volume, Channel, Power).
👉 Easy to use, samajhna easy, kaam jaldi ho jaata hai.

---

## 3. **Code Example**

### ❌ Without KISS (Over-engineering)

```cpp
#include <iostream>
using namespace std;

// Complex function just to find max of 2 numbers
int findMaximum(int a, int b, bool checkEqual = false, bool allowNegative = true) {
    if (!allowNegative && (a < 0 || b < 0)) {
        cout << "Negatives not allowed!" << endl;
        return 0;
    }
    if (checkEqual && a == b) {
        cout << "Both are equal!" << endl;
        return a;
    }
    return (a > b) ? a : b;
}

int main() {
    cout << findMaximum(5, 10) << endl;
    return 0;
}
```

👉 Problem:

* Ek simple kaam ke liye (max nikalna) unnecessary flags, conditions daal diye.
* Code samajhna & maintain karna mushkil ho gaya.

---

### ✅ With KISS (Simple & Clear)

```cpp
#include <iostream>
using namespace std;

int findMax(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    cout << findMax(5, 10) << endl;
    return 0;
}
```

👉 Ab:

* Simple function → easy to read, easy to debug, easy to reuse.

---

## 4. **Why KISS is Important?**

* ✅ **Maintainable** → simple code = easy to modify later.
* ✅ **Debugging fast** → complex structure ke bajaye clear flow.
* ✅ **Performance better** → unnecessary overhead kam.
* ✅ **Team collaboration** → simple code sabko easily samajh aata hai.
* ✅ **Better UX** → simple UI/UX = user ko samajhne me mushkil nahi hoti.

---

## 5. **Famous KISS Examples**

* 🔍 **Google Search**: sirf ek search bar → simplicity ke wajah se sab use karte hain.
* 🍏 **Apple iPhone**: minimal design, intuitive use.
* 🐦 **Twitter (140 char)**: force simplicity in communication.
* 🚗 **Tesla Dashboard**: ek bada touchscreen, clutter-free.

---

## 6. **Steps to Apply KISS in Code**

1. **Solve only required problem** → over-engineering avoid karo.
2. **Avoid unnecessary abstraction** → classes, patterns tabhi use karo jab zarurat ho.
3. **Small, clear functions** → har function ek kaam kare.
4. **Readable naming** → variable aur function ka naam self-explanatory ho.
5. **Refactor** → bar-bar check karo code complex ho raha hai kya.

---

## 7. **Key Takeaway**

👉 **KISS = Keep it Simple, Stupid.**
Jitna simple, utna better.

* Simple code = less bugs, faster development, easy maintenance.
* Complex code = headache for you + team.
---

# ⚡ YAGNI Principle (You Aren’t Gonna Need It)

#### ✅ Meaning

* Don’t build **extra/unnecessary features** that you *think* might be useful in the future.
* Only build what is needed **right now** for current requirements.

---

#### 🎯 Why Follow YAGNI?

1. **Saves Time & Cost** → No wasted effort on unused features.
2. **Keeps Code Simple** → Avoids complexity & technical debt.
3. **Less Bugs** → Fewer unnecessary features = fewer chances of errors.
4. **Faster Delivery** → Focus on delivering value quickly.
5. **Easier Maintenance** → Small, focused code is easier to update later.

---

#### 🛠️ How to Apply YAGNI?

1. **Get clear requirements** → Focus on *must-haves*, skip *nice-to-haves*.
2. **Plan simple solution** → Don’t over-engineer.
3. **Say “NO”** → Reject extra features unless absolutely necessary.
4. **Keep track** → Regularly check if you’re building only what’s needed.

---

#### 🌟 Example

❌ Wrong: While building a **To-Do app**, you add *voice recognition, themes, AI-suggestions* from the start.
✅ Right: Just build **Add, Edit, Delete tasks**. Add fancy stuff later *only if required*.

---

👉 In short:
**KISS + YAGNI = Simple, focused, efficient software** 🚀

---

# GRASP Principles (Simple Explanation)

👉 GRASP = *General Responsibility Assignment Software Patterns*
They help decide **“Which class should do what?”** in Object-Oriented Design.


### 1. **Creator**

📌 *Who should create an object?*
➡ The class that **has the information** or **uses it most** should create it.

✅ Example:
`Library` creates `Book` objects because it knows about them.

```cpp
class Book {
    std::string title;
public:
    Book(std::string t) : title(t) {}
};

class Library {
public:
    Book createBook(std::string title) { 
        return Book(title); 
    }
};
```

---

### 2. **Information Expert**

📌 *Who should do the work?*
➡ The class that has the **required information**.

✅ Example:
`Book` knows if it’s available or not, so checking availability belongs to `Book`, not `Library`.

```cpp
class Book {
    bool available;
public:
    Book(bool a) : available(a) {}
    bool isAvailable() { return available; }  // Info expert
};
```

---

### 3. **Low Coupling**

📌 *Classes should depend less on each other.*
➡ If one changes, others should not break.

✅ Example:
Use an **interface** instead of directly connecting `Library` to `BookDatabase`.

```cpp
class IBookData {
public:
    virtual bool checkAvailability(std::string title) = 0;
};

class BookDatabase : public IBookData {
public:
    bool checkAvailability(std::string title) override { return true; }
};
```

---

### 4. **High Cohesion**

📌 *Each class should have one clear purpose.*
➡ Don’t mix responsibilities.

✅ Example:
`Book` → handles only book details.
`User` → handles user details.

---

### 5. **Controller**

📌 *Who handles input/requests?*
➡ Use a **Controller class** to coordinate actions.

✅ Example:
When a user borrows a book, `LibraryController` handles it.

```cpp
class LibraryController {
public:
    void borrowBook(std::string user, std::string book) {
        std::cout << user << " borrowed " << book << "\n";
    }
};
```

---

### 6. **Pure Fabrication**

📌 *Make a helper class if needed.*
➡ Even if it doesn’t represent a real-world thing.

✅ Example:
Instead of putting email logic inside `User`, create a `NotificationService`.

```cpp
class NotificationService {
public:
    void sendEmail(std::string msg) {
        std::cout << "Email: " << msg << "\n";
    }
};
```

---

### 7. **Indirection**

📌 *Use a middle layer to reduce direct dependency.*
➡ Example: Introduce a `Repository` instead of directly using the database.

✅ Example:
`Library` talks to `BookRepository`, not directly to DB.

---

### 8. **Polymorphism**

📌 *Different types, same interface.*
➡ Handle behavior differently using inheritance/interfaces.

✅ Example:
E-book vs Printed book borrowing rules.

```cpp
class Book {
public:
    virtual void borrow() = 0;
};

class EBook : public Book {
public:
    void borrow() override { std::cout << "Borrowed EBook\n"; }
};

class PrintedBook : public Book {
public:
    void borrow() override { std::cout << "Borrowed Printed Book\n"; }
};
```

---

# 🎯 Quick Memory Trick

* **Creator** → Who makes objects?
* **Info Expert** → Who knows enough to do it?
* **Low Coupling** → Keep classes independent.
* **High Cohesion** → Each class has a single job.
* **Controller** → Middleman for requests.
* **Pure Fabrication** → Extra helper class.
* **Indirection** → Use a middle layer.
* **Polymorphism** → Different types, same behavior.
