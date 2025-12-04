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
