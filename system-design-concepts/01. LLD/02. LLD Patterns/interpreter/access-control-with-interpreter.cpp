#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

// Context: Stores user permissions
class Context {
    unordered_map<string, bool> permissions;
public:
    void setPermission(const string& name, bool value) {
        permissions[name] = value;
    }
    bool getPermission(const string& name) {
        return permissions[name];
    }
};

// Abstract Expression
class Expression {
public:
    virtual bool interpret(Context& context) = 0;
    virtual ~Expression() {}
};

// Terminal Expression: Check a single permission
class Permission : public Expression {
    string name;
public:
    Permission(const string& n) : name(n) {}
    bool interpret(Context& context) override {
        return context.getPermission(name);
    }
};

// Non-Terminal Expression: AND
class AndExpression : public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    AndExpression(unique_ptr<Expression> l, unique_ptr<Expression> r) 
        : left(move(l)), right(move(r)) {}
    bool interpret(Context& context) override {
        return left->interpret(context) && right->interpret(context);
    }
};

// Non-Terminal Expression: OR
class OrExpression : public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    OrExpression(unique_ptr<Expression> l, unique_ptr<Expression> r) 
        : left(move(l)), right(move(r)) {}
    bool interpret(Context& context) override {
        return left->interpret(context) || right->interpret(context);
    }
};

// ✅ Client
int main() {
    Context userContext;
    userContext.setPermission("Admin", false);
    userContext.setPermission("Manager", true);
    userContext.setPermission("ReadPermission", true);
    userContext.setPermission("WritePermission", false);

    // Expression: Admin OR (Manager AND ReadPermission)
    unique_ptr<Expression> accessRule = make_unique<OrExpression>(
        make_unique<Permission>("Admin"),
        make_unique<AndExpression>(
            make_unique<Permission>("Manager"),
            make_unique<Permission>("ReadPermission")
        )
    );

    if (accessRule->interpret(userContext))
        cout << "Access Granted ✅\n";
    else
        cout << "Access Denied ❌\n";

    return 0;
}

// WHY -> Interpreter Pattern 

// Imagine a system where users have roles, and we want to interpret access rules dynamically.
// For example:

// "Admin OR (Manager AND ReadPermission)"

// "Employee AND WritePermission"

// We can model this with the Interpreter Pattern.

// 🟢 Dry Run

// User:

// Admin = false

// Manager = true

// ReadPermission = true

// Rule: Admin OR (Manager AND ReadPermission)

// Interpretation:

// Admin OR (Manager AND ReadPermission)
// false OR (true AND true)
// false OR true => true


// ✅ Access Granted

// 🔑 Why This is Useful

// We can add new rules dynamically without changing code.

// Expressions can be nested arbitrarily (AND, OR, NOT).

// Very common in RBAC (Role-Based Access Control), workflow engines, and policy evaluation systems.