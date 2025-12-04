#include <bits/stdc++.h>
using namespace std;

class Student
{
public:
    string name;
    Student(const string &n) : name(n) {}
};

class Teacher
{
public:
    string name;
    vector<Student *> students;

    Teacher(const string &n) : name(n) {}

    void addStudent(Student *s)
    {
        students.push_back(s);
    }

    void printStudents() const
    {
        cout << "Teacher " << name << " has students:\n";
        for (const auto *s : students)
        {
            cout << " - " << s->name << "\n";
        }
    }
};
int main()
{
    Student  alice("Alice");
    Student  bob("Bob");

    Teacher mrSmit("MR Smith");
    mrSmit.addStudent(&alice);
    mrSmit.addStudent(&bob);

    mrSmit.printStudents();
    return 0;
}
