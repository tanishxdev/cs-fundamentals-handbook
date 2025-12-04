#include <iostream>
using namespace std;

/*
============================================================
PROTOTYPE BASE CLASS
Defines interface for cloning
============================================================
*/
class Prototype {
public:
    virtual Prototype* clone() = 0;
    virtual void show() = 0;
    virtual ~Prototype() {}
};

/*
============================================================
CONCRETE PROTOTYPE
Implements clone logic
============================================================
*/
class GameCharacter : public Prototype {
private:
    string name;
    int health;
    int power;

public:
    GameCharacter(string n, int h, int p) {
        cout << "Expensive character creation...\n";
        name = n;
        health = h;
        power = p;
    }

    // CLONE METHOD (Core of Prototype Pattern)
    Prototype* clone() override {
        return new GameCharacter(*this); // copy existing object
    }

    void show() override {
        cout << name << " | Health: " << health << " | Power: " << power << endl;
    }
};

int main() {

    // Create original object only once
    GameCharacter* original = new GameCharacter("Warrior", 100, 50);

    // Clone instead of creating new
    Prototype* c1 = original->clone();
    Prototype* c2 = original->clone();

    original->show();
    c1->show();
    c2->show();
}
