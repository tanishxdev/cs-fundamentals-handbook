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
};

int main() {
    TodoApp app;
    app.addTask("Finish homework");
    app.addTask("Go to gym");

    app.showTasks();  // ✅ Only required functionality
    return 0;
}
/*
✅ With YAGNI (Simple & Focused)

Here, we only add what’s required right now → Add & Show tasks.

🔑 Key Takeaway

❌ Without YAGNI → Extra features increase complexity, bugs, time.
✅ With YAGNI → Only current needs are handled → simple, clean, fast.
*/

