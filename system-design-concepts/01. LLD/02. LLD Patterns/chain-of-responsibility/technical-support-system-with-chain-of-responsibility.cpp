// 🔴 Problem: Sometimes a request may be handled by multiple people depending on conditions (e.g., leave approval → Manager, HR, Director). If one person cannot handle it, they pass it to the next.

// 🟢 Solution (CoR): We make a chain of handlers, each deciding:
// Can I handle this request? → If yes, process.
// If not → Pass to the next handler.

// This removes huge if-else ladders and makes code flexible (easy to add/remove handlers).

// ⚒️ Flow (Dry Run)
// Request 1 (2 days):
// Manager → days = 2 ≤ 3 → Manager approves ✅.

// Request 2 (5 days):
// Manager → can’t approve (days > 3) → passes to HR.

// HR → days = 5 ≤ 7 → HR approves ✅.
// Request 3 (10 days):

// Manager → can’t approve (days > 3).
// HR → can’t approve (days > 7).

// Director → final approver → approves ✅.

// 🤔 Why CoR is Useful
// Avoids big if-else chains like:
// if (days <= 3) { ... }
// else if (days <= 7) { ... }
// else { ... }

// Easy to add new approvers (just extend chain).
// Flexible: order of chain can change at runtime.

// ✅ So the logic:
// Each handler either handles the request or forwards it → until some handler processes it.

#include <iostream>
#include <string>
using namespace std;

// Request Class
class LeaveRequest {
public:
    string employeeName;
    int days;
    LeaveRequest(string name, int d) : employeeName(name), days(d) {}
};

// Abstract Handler
class Approver {
protected:
    Approver* nextApprover;
public:
    Approver() : nextApprover(nullptr) {}
    void setNext(Approver* next) { nextApprover = next; }

    virtual void approveLeave(LeaveRequest request) {
        if (nextApprover != nullptr)
            nextApprover->approveLeave(request);
        else
            cout << "No approver available for " << request.days << " days leave.\n";
    }
    virtual ~Approver() {}
};

// Concrete Handler 1: Manager
class Manager : public Approver {
public:
    void approveLeave(LeaveRequest request) override {
        if (request.days <= 3) {
            cout << "Manager approved " << request.days 
                 << " days leave for " << request.employeeName << ".\n";
        } else if (nextApprover != nullptr) {
            nextApprover->approveLeave(request);
        }
    }
};

// Concrete Handler 2: HR
class HR : public Approver {
public:
    void approveLeave(LeaveRequest request) override {
        if (request.days <= 7) {
            cout << "HR approved " << request.days 
                 << " days leave for " << request.employeeName << ".\n";
        } else if (nextApprover != nullptr) {
            nextApprover->approveLeave(request);
        }
    }
};

// Concrete Handler 3: Director
class Director : public Approver {
public:
    void approveLeave(LeaveRequest request) override {
        cout << "Director approved " << request.days 
             << " days leave for " << request.employeeName << ".\n";
    }
};

// Client
int main() {
    // Create Approvers
    Manager manager;
    HR hr;
    Director director;

    // Build Chain: Manager -> HR -> Director
    manager.setNext(&hr);
    hr.setNext(&director);

    // Requests
    LeaveRequest req1("PersonA", 2);
    LeaveRequest req2("PersonB", 5);
    LeaveRequest req3("", 10);

    manager.approveLeave(req1); // handled by Manager
    manager.approveLeave(req2); // passed to HR
    manager.approveLeave(req3); // passed to Director

    return 0;
}
