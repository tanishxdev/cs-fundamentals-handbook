# Memento Design Pattern

## 1. **What it is?**

The **Memento Pattern** lets you **save and restore the state of an object** without exposing its internal details.

Think of it like **checkpoints in a video game**:

* You save progress → (create a snapshot of the state).
* Later, you can load progress → (restore from snapshot).

---

## 2. **Why do we need it?**

* Sometimes you want **undo/redo** functionality.
* Or **rollback** to a previous state.
* You don’t want to expose internal object details (encapsulation).

Without Memento → you might keep exposing variables everywhere → breaks OOP principles.

![Communication between the components](https://media.geeksforgeeks.org/wp-content/uploads/20240209165245/Communication-between-components-(1).webp)
---

## 3. **Real-World Examples**

* **Text Editors (Ctrl+Z / Undo)** – Save states of text.
* **Video Games** – Save checkpoints.
* **Banking Transactions** – Rollback to previous state if something fails.
![Memento General UML](https://media.geeksforgeeks.org/wp-content/uploads/20240604120233/2-(1).webp)

---

## 4. **How it works (Roles)**

* **Originator** → The object whose state we want to save (e.g., TextEditor).
* **Memento** → The snapshot (stores state).
* **Caretaker** → Manages history of Mementos (undo/redo).

---

## 5. **C++ Implementation**

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 🎯 Memento: stores state
class Memento {
    string state;
public:
    Memento(string s) : state(s) {}
    string getState() { return state; }
};

// 🎯 Originator: the object whose state we want to save/restore
class TextEditor {
    string text;
public:
    void type(const string& words) {
        text += words;
    }

    string getText() {
        return text;
    }

    // Save state into Memento
    Memento save() {
        return Memento(text);
    }

    // Restore state from Memento
    void restore(Memento m) {
        text = m.getState();
    }
};

// 🎯 Caretaker: manages history of Mementos
class History {
    vector<Memento> savedStates;
public:
    void push(Memento m) {
        savedStates.push_back(m);
    }

    Memento pop() {
        if (savedStates.empty()) {
            throw runtime_error("No states saved!");
        }
        Memento m = savedStates.back();
        savedStates.pop_back();
        return m;
    }
};

// ✅ Client
int main() {
    TextEditor editor;
    History history;

    // Typing text
    editor.type("Hello ");
    editor.type("World!");
    cout << "Current: " << editor.getText() << endl;

    // Save state (checkpoint)
    history.push(editor.save());

    editor.type(" Adding more text...");
    cout << "After typing: " << editor.getText() << endl;

    // Undo (restore last state)
    editor.restore(history.pop());
    cout << "After undo: " << editor.getText() << endl;

    return 0;
}
```
![Communication between the components](https://media.geeksforgeeks.org/wp-content/uploads/20240604120300/1-(1).webp)

---

## 6. **Dry Run**

1. Type: `"Hello World!"`
   Save this state in history.

2. Type: `" Adding more text..."`
   Current text → `"Hello World! Adding more text..."`

3. Undo → restore from saved Memento.
   Text becomes `"Hello World!"`. ✅

---

## 7. **Complexity**

* Saving state = O(1) (copying small state) or O(n) if large objects.
* Restoring = O(1).
* Caretaker can store **multiple checkpoints**.

---

✅ **Memento is useful wherever you need undo/redo, checkpoints, or rollback functionality**.
