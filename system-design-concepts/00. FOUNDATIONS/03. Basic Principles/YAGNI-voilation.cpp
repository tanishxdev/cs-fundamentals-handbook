#include <iostream>
#include <vector>
#include <string>

class TodoApp {
    std::vector<std::string> tasks;
public:
    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    void showTasks() {
        std::cout << "Your Tasks:\n";
        for (int i = 0; i < tasks.size(); i++) {
            std::cout << i + 1 << ". " << tasks[i] << "\n";
        }
    }

    // ❌ Extra features (not needed right now)
    void changeTheme(std::string theme) {
        std::cout << "Theme changed to " << theme << "\n";
    }

    void voiceAddTask(std::string voiceInput) {
        std::cout << "Voice task added: " << voiceInput << "\n";
        tasks.push_back(voiceInput);
    }
};

int main() {
    TodoApp app;
    app.addTask("Finish homework");
    app.addTask("Go to gym");

    // Extra, unnecessary features
    app.changeTheme("Dark");
    app.voiceAddTask("Buy groceries");

    app.showTasks();
    return 0;
}
/*
❌ Without YAGNI (Over-engineered)

Here, the developer adds extra features (like themes & voice commands) even though the requirement is just a simple To-Do list.*/
