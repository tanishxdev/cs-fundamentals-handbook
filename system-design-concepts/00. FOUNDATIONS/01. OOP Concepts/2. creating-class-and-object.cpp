#include <bits/stdc++.h>
using namespace std;

class Student
{
public:
    int roll;
    string name;

    void takeLeave()
    {
        cout << "on leave" << endl;
    }
    void bunkClass()
    {
        cout << "Go out and play: " << endl;
    }
};

int main()
{
    Student s1;

    s1.bunkClass();       // calls the method
    s1.name = "John Doe"; // sets the name
    s1.roll = 1;          // sets the roll number
    cout << s1.name << endl;
    return 0;
}

