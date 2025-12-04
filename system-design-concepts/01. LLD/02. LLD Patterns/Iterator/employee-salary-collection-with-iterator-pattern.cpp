#include <iostream>
#include <vector>
#include <list>
using namespace std;

// -------------------- Employee --------------------
class Employee {
    string name;
    double salary;
public:
    Employee(string n, double s) : name(n), salary(s) {}
    double getSalary() const { return salary; }
    string getName() const { return name; }
};

// -------------------- Iterator Interface --------------------
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

// -------------------- Aggregate Interface --------------------
template <typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~Aggregate() {}
};

// -------------------- Vector Iterator --------------------
class VectorEmployeeIterator : public Iterator<Employee*> {
private:
    vector<Employee*>& employees;
    size_t index;
public:
    VectorEmployeeIterator(vector<Employee*>& e) : employees(e), index(0) {}
    bool hasNext() override { return index < employees.size(); }
    Employee* next() override { return employees[index++]; }
};

// -------------------- List Iterator --------------------
class ListEmployeeIterator : public Iterator<Employee*> {
private:
    list<Employee*>& employees;
    list<Employee*>::iterator it;
public:
    ListEmployeeIterator(list<Employee*>& e) : employees(e), it(employees.begin()) {}
    bool hasNext() override { return it != employees.end(); }
    Employee* next() override { return *it++; }
};

// -------------------- VectorEmployeeCollection --------------------
class VectorEmployeeCollection : public Aggregate<Employee*> {
private:
    vector<Employee*> employees;
public:
    void addEmployee(Employee* e) { employees.push_back(e); }
    Iterator<Employee*>* createIterator() override {
        return new VectorEmployeeIterator(employees);
    }
};

// -------------------- ListEmployeeCollection --------------------
class ListEmployeeCollection : public Aggregate<Employee*> {
private:
    list<Employee*> employees;
public:
    void addEmployee(Employee* e) { employees.push_back(e); }
    Iterator<Employee*>* createIterator() override {
        return new ListEmployeeIterator(employees);
    }
};

// -------------------- Client Code --------------------
int main() {
    // Collection 1: Vector
    VectorEmployeeCollection vectorEmployees;
    vectorEmployees.addEmployee(new Employee("Alice", 50000));
    vectorEmployees.addEmployee(new Employee("Bob", 60000));

    // Collection 2: List
    ListEmployeeCollection listEmployees;
    listEmployees.addEmployee(new Employee("Charlie", 55000));
    listEmployees.addEmployee(new Employee("Diana", 70000));

    // Iterate without knowing collection type
    double totalSalary = 0;

    Iterator<Employee*>* it1 = vectorEmployees.createIterator();
    while (it1->hasNext()) {
        Employee* emp = it1->next();
        cout << emp->getName() << " earns " << emp->getSalary() << endl;
        totalSalary += emp->getSalary();
    }
    delete it1;

    Iterator<Employee*>* it2 = listEmployees.createIterator();
    while (it2->hasNext()) {
        Employee* emp = it2->next();
        cout << emp->getName() << " earns " << emp->getSalary() << endl;
        totalSalary += emp->getSalary();
    }
    delete it2;

    cout << "Total Salary Expense = " << totalSalary << endl;

    return 0;
}
