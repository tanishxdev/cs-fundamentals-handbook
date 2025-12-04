#include <iostream>
using namespace std;

class GameCharacter {
public:
    string name;
    int health;
    int power;

    GameCharacter(string n, int h, int p) {
        cout << "Expensive character creation...\n";
        name = n;
        health = h;
        power = p;
    }

    void show() {
        cout << name << " | Health: " << health << " | Power: " << power << endl;
    }
};

int main() {
    GameCharacter c1("Warrior", 100, 50);
    GameCharacter c2("Warrior", 100, 50);
    GameCharacter c3("Warrior", 100, 50);

    c1.show();
    c2.show();
    c3.show();
}
