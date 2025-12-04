#include <iostream>
#include <vector>
using namespace std;

// 🎯 Memento: Stores snapshot of player state
class PlayerMemento {
    int health;
    int level;
    string position;
public:
    PlayerMemento(int h, int l, string p) : health(h), level(l), position(p) {}
    int getHealth() { return health; }
    int getLevel() { return level; }
    string getPosition() { return position; }
};

// 🎯 Originator: Player whose state we save/restore
class Player {
    int health;
    int level;
    string position;
public:
    Player(int h, int l, string p) : health(h), level(l), position(p) {}

    void setState(int h, int l, string p) {
        health = h; level = l; position = p;
    }

    void showState() {
        cout << "Player [Health: " << health
             << ", Level: " << level
             << ", Position: " << position << "]\n";
    }

    // Save checkpoint
    PlayerMemento save() {
        return PlayerMemento(health, level, position);
    }

    // Restore from checkpoint
    void restore(PlayerMemento m) {
        health = m.getHealth();
        level = m.getLevel();
        position = m.getPosition();
    }
};

// 🎯 Caretaker: Stores checkpoints
class GameHistory {
    vector<PlayerMemento> saves;
public:
    void push(PlayerMemento m) { saves.push_back(m); }
    PlayerMemento pop() {
        if (saves.empty()) throw runtime_error("No saves found!");
        PlayerMemento m = saves.back();
        saves.pop_back();
        return m;
    }
};

// ✅ Client
int main() {
    Player player(100, 1, "StartPoint");
    GameHistory history;

    cout << "Game Start:\n";
    player.showState();

    // Save checkpoint 1
    history.push(player.save());

    // Player progresses
    player.setState(80, 2, "Forest");
    cout << "\nAfter fight:\n";
    player.showState();

    // Save checkpoint 2
    history.push(player.save());

    // Player loses badly
    player.setState(30, 3, "Dungeon");
    cout << "\nAfter Boss fight:\n";
    player.showState();

    // Rollback (Undo)
    cout << "\nUndo to last checkpoint:\n";
    player.restore(history.pop());
    player.showState();

    cout << "\nUndo to start checkpoint:\n";
    player.restore(history.pop());
    player.showState();

    return 0;
}


// 🔑 Key Points

// Player = Originator
// PlayerMemento = Stores snapshot (health, level, position)
// GameHistory = Caretaker (manages checkpoints)
// Supports multiple undo levels (like checkpoints in real games).