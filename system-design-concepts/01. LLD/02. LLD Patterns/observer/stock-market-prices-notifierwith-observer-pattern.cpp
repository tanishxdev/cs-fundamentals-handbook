#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Observer Interface
class Observer {
public:
    virtual void update(float price) = 0;
    virtual ~Observer() {}
};

// Subject Interface
class Subject {
public:
    virtual void addObserver(Observer* obs) = 0;
    virtual void removeObserver(Observer* obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};

// Concrete Subject: Stock
class Stock : public Subject {
private:
    float price;
    vector<Observer*> observers;

public:
    void addObserver(Observer* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (auto* obs : observers) {
            obs->update(price);
        }
    }

    void setPrice(float newPrice) {
        price = newPrice;
        cout << "\n[Stock] Price updated to: $" << price << endl;
        notifyObservers();
    }
};

// Concrete Observer: Investor
class Investor : public Observer {
private:
    string name;
public:
    Investor(string n) : name(n) {}
    void update(float price) override {
        cout << name << " got notified -> New Stock Price: $" << price << endl;
    }
};

// Client
int main() {
    Stock appleStock;

    Investor i1("Alice");
    Investor i2("Bob");

    // Investors subscribe to stock
    appleStock.addObserver(&i1);
    appleStock.addObserver(&i2);

    // Stock price updates
    appleStock.setPrice(150.0);
    appleStock.setPrice(160.5);

    // Bob unsubscribes
    appleStock.removeObserver(&i2);
    appleStock.setPrice(170.2);

    return 0;
}
