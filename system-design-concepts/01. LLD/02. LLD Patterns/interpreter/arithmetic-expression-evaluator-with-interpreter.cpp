#include <iostream>
#include <memory>
using namespace std;

// 🎯 Abstract Expression
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() {}
};

// 🎯 Terminal Expression: Number
class Number : public Expression {
    int value;
public:
    Number(int v) : value(v) {}
    int interpret() override { return value; }
};

// 🎯 Non-Terminal Expression: Addition
class Add : public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    Add(unique_ptr<Expression> l, unique_ptr<Expression> r) : left(move(l)), right(move(r)) {}
    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

// 🎯 Non-Terminal Expression: Subtraction
class Subtract : public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    Subtract(unique_ptr<Expression> l, unique_ptr<Expression> r) : left(move(l)), right(move(r)) {}
    int interpret() override {
        return left->interpret() - right->interpret();
    }
};

// ✅ Client
int main() {
    // Expression: (5 + 10) - 3
    unique_ptr<Expression> expr = make_unique<Subtract>(
        make_unique<Add>(
            make_unique<Number>(5),
            make_unique<Number>(10)
        ),
        make_unique<Number>(3)
    );

    cout << "Result: " << expr->interpret() << endl; // Output: 12
    return 0;
}

// Key Notes

// Terminal Expressions: Basic elements (Numbers, Booleans, literals).

// Non-Terminal Expressions: Combine terminals (Add, Multiply, And, Or).

// Can be extended to complex grammar easily.

// Useful for interpreting rules dynamically without changing code.