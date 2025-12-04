#include <iostream>
#include <string>
using namespace std;

// 🎯 Interface (Abstract class with pure virtual functions)
class Owner {
public:
    virtual void acquire(const string& property) = 0;   // pure virtual
    virtual void dispose(const string& property) = 0;   // pure virtual
    virtual ~Owner() = default; // virtual destructor for safety
};

// 👤 Person realizes Owner
class Person : public Owner {
public:
    void acquire(const string& property) override {
        cout << "Person acquired " << property << endl;
    }
    void dispose(const string& property) override {
        cout << "Person disposed " << property << endl;
    }
};

// 🏢 Corporation realizes Owner
class Corporation : public Owner {
public:
    void acquire(const string& property) override {
        cout << "Corporation acquired " << property << endl;
    }
    void dispose(const string& property) override {
        cout << "Corporation disposed " << property << endl;
    }
};

int main() {
    // Polymorphism using Interface
    Owner* o1 = new Person();
    Owner* o2 = new Corporation();

    o1->acquire("House");
    o2->acquire("Office");

    o1->dispose("Car");
    o2->dispose("Company Vehicle");

    delete o1;
    delete o2;
    return 0;
}
