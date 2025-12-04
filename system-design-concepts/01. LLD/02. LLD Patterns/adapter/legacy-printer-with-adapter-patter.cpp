#include <iostream>
using namespace std;

// --- 1️⃣ Target Interface ---
class Printer {
public:
    virtual void print() = 0;  // Expected by the new system
    virtual ~Printer() {}
};

// --- 2️⃣ Adaptee (Legacy System) ---
class LegacyPrinter {
public:
    void printDocument() {  // Old incompatible method
        cout << "🖨️ Legacy Printer is printing a document..." << endl;
    }
};

// --- 3️⃣ Adapter ---
class PrinterAdapter : public Printer {
private:
    LegacyPrinter* legacyPrinter;  // Composition (has-a relationship)
public:
    PrinterAdapter(LegacyPrinter* lp) : legacyPrinter(lp) {}

    void print() override {  // Adapts new method to old one
        legacyPrinter->printDocument();
    }
};

// --- 4️⃣ Client ---
int main() {
    LegacyPrinter* oldPrinter = new LegacyPrinter();

    // Adapter allows the new system to use old printer
    Printer* printer = new PrinterAdapter(oldPrinter);

    cout << "🧩 Using Adapter Pattern:" << endl;
    printer->print();

    // Cleanup
    delete oldPrinter;
    delete printer;
    return 0;
}
