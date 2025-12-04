#include <iostream>
using namespace std;

// Base Class
class GameCharacter {
public:
    // Template Method (fixed sequence of actions)
    void takeTurn() {
        selectTarget();
        move();
        attack();       // differs per character
        updateHealth();
    }

    void selectTarget() { cout << "Selecting target...\n"; }
    void move() { cout << "Moving to position...\n"; }
    void updateHealth() { cout << "Updating health and status...\n"; }

    // Abstract step
    virtual void attack() = 0;
};

// Concrete Class 1: Warrior
class Warrior : public GameCharacter {
public:
    void attack() override {
        cout << "Warrior attacks with a sword slash!\n";
    }
};

// Concrete Class 2: Mage
class Mage : public GameCharacter {
public:
    void attack() override {
        cout << "Mage casts a fireball spell!\n";
    }
};

// Concrete Class 3: Archer
class Archer : public GameCharacter {
public:
    void attack() override {
        cout << "Archer shoots an arrow!\n";
    }
};

// Client
int main() {
    cout << "--- Warrior's Turn ---\n";
    Warrior warrior;
    warrior.takeTurn();

    cout << "\n--- Mage's Turn ---\n";
    Mage mage;
    mage.takeTurn();

    cout << "\n--- Archer's Turn ---\n";
    Archer archer;
    archer.takeTurn();

    return 0;
}
