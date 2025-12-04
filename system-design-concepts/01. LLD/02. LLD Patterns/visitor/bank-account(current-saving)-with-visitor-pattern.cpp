
#include <iostream>
#include <vector>
using namespace std;

// Forward declaration of concrete elements
class SavingsAccount;
class CurrentAccount;

// ---------------- Visitor Interface ----------------
class Visitor {
public:
    virtual void visit(SavingsAccount* acc) = 0;
    virtual void visit(CurrentAccount* acc) = 0;
    virtual ~Visitor() {}
};

// ---------------- Element Interface ----------------
class Account {
public:
    virtual void accept(Visitor* v) = 0;
    virtual ~Account() {}
};

// ---------------- Concrete Elements ----------------
class SavingsAccount : public Account {
public:
    string owner;
    double balance;
    SavingsAccount(string o, double b) : owner(o), balance(b) {}
    void accept(Visitor* v) override { v->visit(this); }
};

class CurrentAccount : public Account {
public:
    string owner;
    double balance;
    CurrentAccount(string o, double b) : owner(o), balance(b) {}
    void accept(Visitor* v) override { v->visit(this); }
};

// ---------------- Concrete Visitors ----------------
class InterestVisitor : public Visitor {
public:
    void visit(SavingsAccount* acc) override {
        double interest = acc->balance * 0.04; // 4% for savings
        cout << "Savings Account Interest for " << acc->owner 
             << " = " << interest << endl;
    }
    void visit(CurrentAccount* acc) override {
        double interest = acc->balance * 0.02; // 2% for current
        cout << "Current Account Interest for " << acc->owner 
             << " = " << interest << endl;
    }
};

class StatementVisitor : public Visitor {
public:
    void visit(SavingsAccount* acc) override {
        cout << "[Savings Statement] Owner: " << acc->owner 
             << " | Balance: " << acc->balance << endl;
    }
    void visit(CurrentAccount* acc) override {
        cout << "[Current Statement] Owner: " << acc->owner 
             << " | Balance: " << acc->balance << endl;
    }
};

// ---------------- Client ----------------
int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingsAccount("Alice", 10000));
    accounts.push_back(new CurrentAccount("Bob", 5000));

    InterestVisitor interestCalculator;
    StatementVisitor statementPrinter;

    cout << "--- Interest Calculation ---" << endl;
    for (auto acc : accounts) acc->accept(&interestCalculator);

    cout << "\n--- Account Statements ---" << endl;
    for (auto acc : accounts) acc->accept(&statementPrinter);

    // Cleanup
    for (auto acc : accounts) delete acc;

    return 0;
}

/*
🎯 Operations:

Interest Calculation (different for each account).

Statement Printing (common operation but different format).

Instead of putting calculateInterest() and printStatement() inside every account class,
we’ll use Visitors.

🎯 Why Visitor Fits Here

Adding new operations like TaxVisitor, LoanEligibilityVisitor is super easy.

Without Visitor, you’d have to modify SavingsAccount and CurrentAccount every time.

Visitor keeps object structure stable and moves the operations out.
*/