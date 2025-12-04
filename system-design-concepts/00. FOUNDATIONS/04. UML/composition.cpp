#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Part: Room
class Room {
    string name;
public:
    Room(string n) : name(n) {}
    void show() const { cout << "Room: " << name << "\n"; }
};

// Whole: House (owns Rooms)
class House {
    vector<Room> rooms;  // Composition: House "owns" rooms
public:
    void addRoom(const string& roomName) {
        rooms.emplace_back(roomName);
    }

    void showHouse() const {
        cout << "This house has rooms:\n";
        for (const auto& room : rooms)
            room.show();
    }
};

int main() {
    House myHouse;

    myHouse.addRoom("Living Room");
    myHouse.addRoom("Bedroom");
    myHouse.addRoom("Kitchen");

    myHouse.showHouse();
    // When myHouse is destroyed, all Room objects are also destroyed.
}
