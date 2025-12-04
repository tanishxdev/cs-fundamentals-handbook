#include <iostream>
#include <string>
#include <stack>
using namespace std;

// ----------------- Receiver -----------------
class TextEditor {
private:
    string text;
public:
    void write(const string& newText) {
        text += newText;
        cout << "Text after write: " << text << "\n";
    }
    void erase(int count) {
        if (count <= text.size()) {
            text.erase(text.size() - count, count);
        }
        cout << "Text after erase: " << text << "\n";
    }
};

// ----------------- Command Interface -----------------
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// ----------------- Concrete Command: Write -----------------
class WriteCommand : public Command {
private:
    TextEditor& editor;
    string textToWrite;
public:
    WriteCommand(TextEditor& e, string txt) : editor(e), textToWrite(txt) {}
    void execute() override { editor.write(textToWrite); }
    void undo() override { editor.erase(textToWrite.size()); }
};

// ----------------- Invoker -----------------
class CommandManager {
private:
    stack<Command*> history;
public:
    void executeCommand(Command* cmd) {
        cmd->execute();
        history.push(cmd);
    }
    void undoLast() {
        if (!history.empty()) {
            Command* cmd = history.top();
            history.pop();
            cmd->undo();
        }
    }
};

// ----------------- Client -----------------
int main() {
    TextEditor editor;
    CommandManager manager;

    // Create commands
    Command* cmd1 = new WriteCommand(editor, "Hello ");
    Command* cmd2 = new WriteCommand(editor, "World!");
    
    // Execute
    manager.executeCommand(cmd1); // Text after write: Hello
    manager.executeCommand(cmd2); // Text after write: Hello World!
    
    // Undo last command
    manager.undoLast();           // Text after erase: Hello 

    delete cmd1;
    delete cmd2;

    return 0;
}
