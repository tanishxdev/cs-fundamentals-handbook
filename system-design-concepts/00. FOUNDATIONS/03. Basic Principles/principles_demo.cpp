#include <bits/stdc++.h>
using namespace std;

/* ===========================
   1) DRY — Don't Repeat Yourself
===========================*/
namespace DRY {
    double calculateTax(double amount) {
        const double TAX_RATE = 0.18;
        return amount * TAX_RATE;
    }

    struct Order {
        double amount;
        double totalWithTax() const { return amount + calculateTax(amount); }
    };

    void demo() {
        Order o{1000};
        cout << "[DRY] Total: " << o.totalWithTax() << "\n";
    }
}

/* ===========================
   2) KISS — Keep It Simple, Stupid
===========================*/
namespace KISS {
    int findMax(const vector<int>& v) {
        if (v.empty()) return INT_MIN;
        int mx = v[0];
        for (int x : v) if (x > mx) mx = x;
        return mx;
    }

    void demo() {
        vector<int> a{3,5,2,9,1};
        cout << "[KISS] Max: " << findMax(a) << "\n";
    }
}

/* ===========================
   3) YAGNI — You Aren't Gonna Need It
===========================*/
namespace YAGNI {
    struct Logger {
        void info(const string& msg) { cout << "[INFO] " << msg << "\n"; }
    };

    void demo() {
        Logger L;
        L.info("Payment processed");
    }
}

/* ===========================
   4) UML — ASCII (in comments)
===========================*/
namespace UML {
    void demo() {
        cout << "[UML] See comments for ASCII diagrams (in source)\n";
    }
}

/* ===========================
   5) GRASP Principles
===========================*/
namespace GRASP {

    struct Cart {
        vector<double> items;
        void add(double p) { items.push_back(p); }
        double total() const {
            double s = 0;
            for (double p : items) s += p;
            return s;
        }
    };

    struct Order {
        Cart cart;
        double tax;
        Order(const Cart& c, double t) : cart(c), tax(t) {}

        static Order createFromCart(const Cart& c) {
            double t = c.total() * 0.18;
            return Order(c, t);
        }

        double grandTotal() const { return cart.total() + tax; }
    };

    struct OrderController {
        static Order handleCreateOrder(const Cart& c) {
            return Order::createFromCart(c);
        }
    };

    void demo() {
        Cart c;
        c.add(200);
        c.add(300);
        Order o = OrderController::handleCreateOrder(c);
        cout << "[GRASP] Grand Total: " << o.grandTotal() << "\n";
    }
}

/* ===========================
   MAIN
===========================*/
int main() {
    cout << "=========== Principles Demo ===========\n";
    DRY::demo();
    KISS::demo();
    YAGNI::demo();
    UML::demo();
    GRASP::demo();
    cout << "=======================================\n";
    return 0;
}
