#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declaration
class User;

// ---------------- Mediator Interface ----------------
class ChatMediator {
public:
    virtual void addUser(User* user) = 0;
    virtual void sendMessage(string msg, User* sender) = 0;
    virtual ~ChatMediator() {}
};

// ---------------- Colleague ----------------
class User {
protected:
    ChatMediator* mediator;
    string name;
public:
    User(ChatMediator* med, string n) : mediator(med), name(n) {}
    virtual void send(string msg) = 0;
    virtual void receive(string msg, string senderName) = 0;
    string getName() { return name; }
    virtual ~User() {}
};

// ---------------- Concrete Mediator ----------------
class ChatRoom : public ChatMediator {
private:
    vector<User*> users;
public:
    void addUser(User* user) override {
        users.push_back(user);
    }

    void sendMessage(string msg, User* sender) override {
        for (auto user : users) {
            if (user != sender) { // don't send to self
                user->receive(msg, sender->getName());
            }
        }
    }
};

// ---------------- Concrete Colleague ----------------
class ConcreteUser : public User {
public:
    ConcreteUser(ChatMediator* med, string n) : User(med, n) {}
    void send(string msg) override {
        cout << name << " sends: " << msg << endl;
        mediator->sendMessage(msg, this);
    }
    void receive(string msg, string senderName) override {
        cout << name << " received from " << senderName << ": " << msg << endl;
    }
};

// ---------------- Client ----------------
int main() {
    ChatRoom chat;

    User* alice = new ConcreteUser(&chat, "Alice");
    User* bob   = new ConcreteUser(&chat, "Bob");
    User* charlie = new ConcreteUser(&chat, "Charlie");

    chat.addUser(alice);
    chat.addUser(bob);
    chat.addUser(charlie);

    alice->send("Hi everyone!");
    bob->send("Hello Alice!");
    charlie->send("Hey folks!");

    delete alice;
    delete bob;
    delete charlie;
    return 0;
}
