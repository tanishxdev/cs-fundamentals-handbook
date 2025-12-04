#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------------------
👉 Problem: Demonstrate Encapsulation in C++
--------------------------------------------------------------
We need to design an Employee class that:
- Hides its data members (id, name)
- Allows controlled access through public getter and setter methods
- Prevents direct modification of private data
--------------------------------------------------------------
*/

// Class Definition for Employee
class Employee {
private: 
    int id;         // private data member to store employee ID
    string name;    // private data member to store employee name

public:
    // ----------------------------------------------------------
    // Setter Method for 'id'
    // Purpose: Assigns a value to private variable 'id'
    // Input: integer id
    // ----------------------------------------------------------
    void setId(int id){
        this->id = id;  
        // 'this->id' refers to the class's member variable
        // 'id' on right side is the function parameter
    }

    // ----------------------------------------------------------
    // Setter Method for 'name'
    // Purpose: Assigns a value to private variable 'name'
    // Input: string name
    // ----------------------------------------------------------
    void setName(string name){
        this->name = name;  
        // Correct assignment
        // 'this->name' ensures we modify the object's data member
    }

    // ----------------------------------------------------------
    // Getter Method for 'id'
    // Purpose: Returns private member 'id'
    // Output: integer value of id
    // ----------------------------------------------------------
    int getId(){
        return id;  // returns the employee ID to caller
    }

    // ----------------------------------------------------------
    // Getter Method for 'name'
    // Purpose: Returns private member 'name'
    // Output: string value of name
    // ----------------------------------------------------------
    string getName(){
        return name;  // returns the employee name to caller
    }
};

// ----------------------------------------------------------
// main() Function — Entry Point
// Demonstrates Encapsulation by interacting with Employee object
// ----------------------------------------------------------
int main()
{
    Employee emp;  // Create an Employee object (instance)

    // Set employee details using setters (controlled access)
    emp.setId(1);            // assigns 1 to emp.id safely
    emp.setName("Alice");    // assigns "Alice" to emp.name safely

    // Print employee details using getters (controlled read access)
    cout << "ID: " << emp.getId() << endl;
    cout << "Name: " << emp.getName() << endl;

    return 0; // end of program
}
