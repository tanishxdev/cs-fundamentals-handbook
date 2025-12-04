#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// Forward declaration for Visitor
class Visitor;

// ---------------------- Abstract Course ----------------------
class Courses_At_GFG {
public:
    virtual void accept(Visitor& visitor) = 0; // Visitor entry point
    virtual string name() const = 0;
    virtual ~Courses_At_GFG() = default;
};

// ---------------------- Concrete Courses ----------------------
class SDE : public Courses_At_GFG {
public:
    void accept(Visitor& visitor) override;
    string name() const override { return "SDE"; }
};

class STL : public Courses_At_GFG {
public:
    void accept(Visitor& visitor) override;
    string name() const override { return "STL"; }
};

class DSA : public Courses_At_GFG {
public:
    void accept(Visitor& visitor) override;
    string name() const override { return "DSA"; }
};

// ---------------------- Abstract Visitor ----------------------
class Visitor {
public:
    virtual void visit(SDE& sde) = 0;
    virtual void visit(STL& stl) = 0;
    virtual void visit(DSA& dsa) = 0;
    virtual ~Visitor() = default;
};

// ---------------------- Concrete Visitors ----------------------
class Instructor : public Visitor {
public:
    void visit(SDE& sde) override {
        cout << sde.name() << " is taught by Instructor." << endl;
    }
    void visit(STL& stl) override {
        cout << stl.name() << " is taught by Instructor." << endl;
    }
    void visit(DSA& dsa) override {
        cout << dsa.name() << " is taught by Instructor." << endl;
    }
};

class Student : public Visitor {
public:
    void visit(SDE& sde) override {
        cout << sde.name() << " is studied by Student." << endl;
    }
    void visit(STL& stl) override {
        cout << stl.name() << " is studied by Student." << endl;
    }
    void visit(DSA& dsa) override {
        cout << dsa.name() << " is studied by Student." << endl;
    }
};

// ✅ New Visitor: Recruiter
class Recruiter : public Visitor {
public:
    void visit(SDE& sde) override {
        cout << "Recruiter visits " << sde.name() 
             << " course to recruit top students!" << endl;
    }
    void visit(STL& stl) override {
        cout << "Recruiter visits " << stl.name() 
             << " course to recruit top students!" << endl;
    }
    void visit(DSA& dsa) override {
        cout << "Recruiter visits " << dsa.name() 
             << " course to recruit top students!" << endl;
    }
};

// ---------------------- accept() Implementations ----------------------
void SDE::accept(Visitor& visitor) { visitor.visit(*this); }
void STL::accept(Visitor& visitor) { visitor.visit(*this); }
void DSA::accept(Visitor& visitor) { visitor.visit(*this); }

// ---------------------- Main ----------------------
int main() {
    // Create Courses
    vector<unique_ptr<Courses_At_GFG>> courses;
    courses.push_back(make_unique<SDE>());
    courses.push_back(make_unique<STL>());
    courses.push_back(make_unique<DSA>());

    // Create Visitors
    Instructor instructor;
    Student student;
    Recruiter recruiter; // ✅ New visitor

    cout << "--- Instructor Visiting ---" << endl;
    for (auto& course : courses) course->accept(instructor);

    cout << "\n--- Student Visiting ---" << endl;
    for (auto& course : courses) course->accept(student);

    cout << "\n--- Recruiter Visiting ---" << endl;
    for (auto& course : courses) course->accept(recruiter);

    return 0;
}
