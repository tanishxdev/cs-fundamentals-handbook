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
