#include <iostream>
#include <vector>
using namespace std;

// Forward declare Visitors
class Visitor;

// ---------------- Element Interface ----------------
class Courses_At_GFG {
public:
    virtual void accept(Visitor* v) = 0; // Must accept a visitor
    virtual string getName() const = 0;  // To print course name
    virtual ~Courses_At_GFG() {}
};

// ---------------- Concrete Elements (Courses) ----------------
class SDE : public Courses_At_GFG {
public:
    void accept(Visitor* v) override;   // defined later
    string getName() const override { return "SDE"; }
};

class STL : public Courses_At_GFG {
public:
    void accept(Visitor* v) override;
    string getName() const override { return "STL"; }
};

class DSA : public Courses_At_GFG {
public:
    void accept(Visitor* v) override;
    string getName() const override { return "DSA"; }
};

// ---------------- Visitor Interface ----------------
class Visitor {
public:
    virtual void visit(SDE* sde) = 0;
    virtual void visit(STL* stl) = 0;
    virtual void visit(DSA* dsa) = 0;
    virtual ~Visitor() {}
};

// ---------------- Concrete Visitors ----------------
class Instructor : public Visitor {
public:
    void visit(SDE* sde) override {
        cout << sde->getName() << " taught by Instructor\n";
    }
    void visit(STL* stl) override {
        cout << stl->getName() << " taught by Instructor\n";
    }
    void visit(DSA* dsa) override {
        cout << dsa->getName() << " taught by Instructor\n";
    }
};

class Student : public Visitor {
public:
    void visit(SDE* sde) override {
        cout << sde->getName() << " studied by Student\n";
    }
    void visit(STL* stl) override {
        cout << stl->getName() << " studied by Student\n";
    }
    void visit(DSA* dsa) override {
        cout << dsa->getName() << " studied by Student\n";
    }
};

// ---------------- Accept Implementations ----------------
void SDE::accept(Visitor* v) { v->visit(this); }
void STL::accept(Visitor* v) { v->visit(this); }
void DSA::accept(Visitor* v) { v->visit(this); }

// ---------------- Client ----------------
int main() {
    // Courses
    vector<Courses_At_GFG*> courses;
    courses.push_back(new SDE());
    courses.push_back(new STL());
    courses.push_back(new DSA());

    // Visitors
    Instructor instructor;
    Student student;

    cout << "--- Instructor Visiting Courses ---\n";
    for (auto c : courses) c->accept(&instructor);

    cout << "\n--- Student Visiting Courses ---\n";
    for (auto c : courses) c->accept(&student);

    // Cleanup
    for (auto c : courses) delete c;

    return 0;
}

/*
🎯 Key Notes

accept(visitor) → lets the visitor decide what to do.

visit() → overloaded for each course type (SDE, STL, DSA).

Adding a new Visitor (e.g., Recruiter) is easy → just implement visit methods.

The course classes never change.
*/
