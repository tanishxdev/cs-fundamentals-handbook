
# What is **Composition**?
![Composition](https://media.geeksforgeeks.org/wp-content/uploads/20250829181817451507/222.webp)
![Composition](https://media.geeksforgeeks.org/wp-content/uploads/20250829121854067732/composition-relationship.webp)
* **Definition**: A “whole–part” relationship where the **whole (parent)** *owns* the **part (child)**.
* If the parent is destroyed → all its parts are destroyed too.
* **UML Notation**:
  → **Solid black diamond** near the parent, and a straight line to the child.

👉 Think: A **House** is composed of **Rooms**. If the house is destroyed, its rooms don’t exist separately.

---

# 📝 Simple Real-Life Example: House and Rooms

### UML View:

```
House ◆─── Room
```

(◆ = filled diamond at House side)

---

### C++ Code

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Part: Room
class Room {
    string name;
public:
    Room(string n) : name(n) {}
    void show() const { cout << "Room: " << name << "\n"; }
};

// Whole: House (owns Rooms)
class House {
    vector<Room> rooms;  // Composition: House "owns" rooms
public:
    void addRoom(const string& roomName) {
        rooms.emplace_back(roomName);
    }

    void showHouse() const {
        cout << "This house has rooms:\n";
        for (const auto& room : rooms)
            room.show();
    }
};

int main() {
    House myHouse;

    myHouse.addRoom("Living Room");
    myHouse.addRoom("Bedroom");
    myHouse.addRoom("Kitchen");

    myHouse.showHouse();
    // When myHouse is destroyed, all Room objects are also destroyed.
}
```

### ✅ Output

```
This house has rooms:
Room: Living Room
Room: Bedroom
Room: Kitchen
```

---

# 🟡 Why is this **Composition**?

* `House` **creates and owns** `Room` objects inside it (`vector<Room>`).
* When `House` goes out of scope → destructor of `House` runs → automatically destroys all `Room` objects.
* `Room` **cannot exist independently** of `House`.

---

# 🔴 Comparison: Aggregation vs Composition

| Feature   | **Aggregation** (loose)       | **Composition** (strong) |
| --------- | ----------------------------- | ------------------------ |
| Ownership | Parent **has** child          | Parent **owns** child    |
| Lifetime  | Child can live without parent | Child dies with parent   |
| UML       | Hollow diamond ◇              | Filled diamond ◆         |

### Example:

* Aggregation: **Teacher–Student** (Students exist without a teacher)
* Composition: **House–Room** (Rooms cannot exist if the house is gone)

---

# 🧠 Another Example: ContactBook (from GFG)

We can also visualize that:

```
ContactBook ◆─── Contact
```

Here, `ContactBook` owns multiple `Contact` objects. If the book is deleted, contacts are gone.

---

# 🚀 Advanced Twist (Dynamic Composition)

Sometimes, instead of storing by **value**, you might store by **pointer** but still control the lifetime using `unique_ptr` (modern C++ best practice):

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
    void start() { cout << "Engine starting...\n"; }
};

class Car {
    unique_ptr<Engine> engine;  // Composition
public:
    Car() : engine(make_unique<Engine>()) {}
    void drive() { engine->start(); cout << "Car is driving...\n"; }
};

int main() {
    Car myCar;   // Engine created automatically
    myCar.drive();
} // When myCar dies -> Engine destroyed automatically
```

✅ This enforces **composition with dynamic memory**, ensuring no leaks.

---

# 🎯 Takeaways

* **Composition = Strong ownership.**
* Parent controls child’s **lifetime**.
* Represented by **solid diamond** in UML.
* Code usually stores **objects directly** (`vector<Room>`) or via smart pointers (`unique_ptr<Contact>`).
