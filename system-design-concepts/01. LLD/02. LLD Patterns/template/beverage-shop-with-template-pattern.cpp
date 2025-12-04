#include <iostream>
using namespace std;

// Abstract Class
class Beverage {
public:
    // Template Method (skeleton of the algorithm)
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    // Common steps (same for all beverages)
    void boilWater() { cout << "Boiling water...\n"; }
    void pourInCup() { cout << "Pouring into cup...\n"; }

    // Steps to be customized by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual ~Beverage() {}
};

// Concrete Class: Tea
class Tea : public Beverage {
public:
    void brew() override {
        cout << "Steeping the tea...\n";
    }
    void addCondiments() override {
        cout << "Adding lemon...\n";
    }
};

// Concrete Class: Coffee
class Coffee : public Beverage {
public:
    void brew() override {
        cout << "Dripping coffee through filter...\n";
    }
    void addCondiments() override {
        cout << "Adding sugar and milk...\n";
    }
};

// Client
int main() {
    cout << "--- Making Tea ---\n";
    Beverage* tea = new Tea();
    tea->prepareRecipe();

    cout << "\n--- Making Coffee ---\n";
    Beverage* coffee = new Coffee();
    coffee->prepareRecipe();

    delete tea;
    delete coffee;

    return 0;
}
/*
* Communication flow of the above example implementation:

* Client Interaction: Imagine you're the person who wants to make a hot beverage, so you decide whether you want tea or coffee.
* Template Method Execution: You follow a predefined set of steps to make your chosen beverage. These steps are outlined in a recipe book (abstract class) that you have.
* Execution Flow within Template Method: You start by boiling water, pouring it into a cup, then you add your specific ingredients depending on whether you're making tea or coffee. These steps are part of the recipe (template method).
* Subclass Implementation: You decide to make tea, so you follow the tea recipe (subclass). In this recipe, instead of adding coffee grounds, you steep a tea bag and add lemon.
* Method Overrides: When you add lemon to your tea, you're customizing that step of the recipe. In programming, this is similar to overriding a method, where you provide your own implementation of a step.
* Inheritance and Polymorphism: You can use the same recipe book (abstract class) to make different beverages (concrete subclasses), whether it's tea or coffee. This is because the recipes (methods) are inherited from the abstract class.
*/
