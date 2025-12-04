## Association vs Aggregation
![dia](https://media.geeksforgeeks.org/wp-content/uploads/20250829181428823664/111.webp)
![dia](https://media.geeksforgeeks.org/wp-content/uploads/20250829115923455181/aggregation.webp)
* **Association** → Just a link, both classes are independent. (e.g., Teacher ↔ Student)
* **Aggregation** → A “whole–part” relationship (HAS-A), but parts can **exist independently** of the whole.
  Example:

  * A **Library** has Books 📚 → Books exist even if Library is destroyed.
  * A **Department** has Teachers 👩‍🏫 → Teachers still exist even if Department is removed.

---

## 📝 Code Explanation (Aggregation)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Teacher {
public:
    string name;
    Teacher(const string& n) : name(n) {}
};

class Department {
private:
    // Aggregation: Department "has a" Teacher
    Teacher* teacher;  

public:
    Department(Teacher* t) : teacher(t) {}

    void showTeacher() const {
        if (teacher)
            cout << "Teacher: " << teacher->name << endl;
    }
};

int main() {
    Teacher t("Dr. Geek");     // Teacher exists independently
    Department dept(&t);       // Department has a Teacher
    dept.showTeacher();

    return 0;
}
```

---

### 🔎 What’s happening here?

1. `Teacher t("Dr. Geek");`
   → Teacher object created (independent).
2. `Department dept(&t);`
   → Department is created with reference to a Teacher.

   * But Department does **not own Teacher’s lifetime**.
   * If Department is destroyed, Teacher still exists.
3. `dept.showTeacher();`
   → Prints Teacher name inside Department.

---

## ✅ Output

```
Teacher: Dr. Geek
```

---

## UML Idea

* **Aggregation Notation** → A hollow diamond (◊) near the “whole” class.

```
 Department ◊---- Teacher
```

* Read as → *Department has-a Teacher*.
* But Teacher can exist without Department.

---

## ⚖️ Quick Difference (Simple Words)

| Relationship    | Example           | Ownership? | Lifetime Dependency         |
| --------------- | ----------------- | ---------- | --------------------------- |
| **Association** | Teacher ↔ Student | None       | Independent                 |
| **Aggregation** | Library ◊→ Book   | Weak       | Part can live without Whole |
| **Composition** | House ◆→ Room     | Strong     | Part dies with Whole        |

---