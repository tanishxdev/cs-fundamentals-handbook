#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // ✅ Needed for std::remove
using namespace std;

// ---------------- Observer Pattern ---------------- //

// Observer Interface
class Observer {
public:
    virtual void update(const string& post, const string& userName) = 0;
    virtual ~Observer() {}
};

// Subject Interface
class Subject {
public:
    virtual void addFollower(Observer* obs) = 0;
    virtual void removeFollower(Observer* obs) = 0;
    virtual void notifyFollowers(const string& post) = 0;
    virtual ~Subject() {}
};

// Concrete Subject: User (someone who can post)
class User : public Subject {
private:
    string name;
    vector<Observer*> followers;

public:
    User(string n) : name(n) {}

    void addFollower(Observer* obs) override {
        followers.push_back(obs);
    }

    void removeFollower(Observer* obs) override {
        followers.erase(remove(followers.begin(), followers.end(), obs), followers.end());
    }

    void notifyFollowers(const string& post) override {
        for (auto* follower : followers) {
            follower->update(post, name);
        }
    }

    void postMessage(const string& post) {
        cout << name << " posted: " << post << endl;
        notifyFollowers(post); // Notify all followers
    }

    string getName() const { return name; }
};

// Concrete Observer: Follower
class Follower : public Observer {
private:
    string name;

public:
    Follower(string n) : name(n) {}

    void update(const string& post, const string& userName) override {
        cout << name << " got notified: " << userName << " posted \"" << post << "\"\n";
    }
};

// ---------------- Client ---------------- //
int main() {
    // Create Users
    User alice("Alice");
    User bob("Bob");

    // Create Followers
    Follower f1("Charlie");
    Follower f2("David");

    // Charlie follows Alice
    alice.addFollower(&f1);

    // David follows Alice and Bob
    alice.addFollower(&f2);
    bob.addFollower(&f2);

    // Alice posts something
    alice.postMessage("Hello World!");

    cout << "-----------------\n";

    // Bob posts something
    bob.postMessage("Good Morning!");

    return 0;
}
