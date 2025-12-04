
#include <iostream>
#include <vector>
using namespace std;

// Forward declare elements
class Book;
class DVD;

// ---------------- Visitor Interface ----------------
class Visitor {
public:
    virtual void visit(Book* b) = 0;
    virtual void visit(DVD* d) = 0;
    virtual ~Visitor() {}
};

// ---------------- Element Interface ----------------
class Item {
public:
    virtual void accept(Visitor* v) = 0;
    virtual ~Item() {}
};

// ---------------- Concrete Elements ----------------
class Book : public Item {
public:
    string title;
    double price;
    Book(string t, double p) : title(t), price(p) {}
    void accept(Visitor* v) override { v->visit(this); }
};

class DVD : public Item {
public:
    string name;
    double price;
    DVD(string n, double p) : name(n), price(p) {}
    void accept(Visitor* v) override { v->visit(this); }
};

// ---------------- Concrete Visitors ----------------
class PrintVisitor : public Visitor {
public:
    void visit(Book* b) override {
        cout << "Book: " << b->title << " | Price: " << b->price << endl;
    }
    void visit(DVD* d) override {
        cout << "DVD: " << d->name << " | Price: " << d->price << endl;
    }
};

class DiscountVisitor : public Visitor {
public:
    void visit(Book* b) override {
        b->price *= 0.9; // 10% discount
        cout << "Discounted Book Price: " << b->price << endl;
    }
    void visit(DVD* d) override {
        d->price *= 0.8; // 20% discount
        cout << "Discounted DVD Price: " << d->price << endl;
    }
};

// ---------------- Client ----------------
int main() {
    vector<Item*> cart;
    cart.push_back(new Book("C++ Design Patterns", 500));
    cart.push_back(new DVD("Interstellar", 300));

    PrintVisitor printer;
    DiscountVisitor discount;

    cout << "--- Original Items ---" << endl;
    for (auto item : cart) item->accept(&printer);

    cout << "--- After Discount ---" << endl;
    for (auto item : cart) item->accept(&discount);

    // Cleanup
    for (auto item : cart) delete item;

    return 0;
}
