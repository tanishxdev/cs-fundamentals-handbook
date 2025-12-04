#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Forward declaration
class Aircraft;

// ---------------- Mediator Interface ----------------
class ATCMediator {
public:
    virtual void registerAircraft(Aircraft* plane) = 0;
    virtual void requestLanding(Aircraft* plane) = 0;
    virtual void requestTakeoff(Aircraft* plane) = 0;
    virtual void notifyEmergency(Aircraft* plane) = 0;
    virtual void runwayVacated() = 0; // called by a plane after using the runway
    virtual ~ATCMediator() {}
};

// ---------------- Aircraft (Colleague) ----------------
class Aircraft {
private:
    string id;
    ATCMediator* atc;
public:
    Aircraft(string id_, ATCMediator* atc_) : id(std::move(id_)), atc(atc_) {
        atc->registerAircraft(this);
    }

    string getId() const { return id; }

    // Request landing via mediator
    void requestLanding() {
        cout << "[" << id << "] requests landing." << endl;
        atc->requestLanding(this);
    }

    // Request takeoff via mediator
    void requestTakeoff() {
        cout << "[" << id << "] requests takeoff." << endl;
        atc->requestTakeoff(this);
    }

    // Notify ATC that this plane needs emergency landing
    void declareEmergency() {
        cout << "[" << id << "] DECLARES EMERGENCY! Needs immediate landing!\n";
        atc->notifyEmergency(this);
    }

    // Called by ATC when permission granted to land
    void land() {
        cout << "[" << id << "] permission granted to LAND. Landing now...\n";
        // simulate landing time...
        cout << "[" << id << "] landed and cleared runway.\n";
        atc->runwayVacated();
    }

    // Called by ATC when permission granted to take off
    void takeoff() {
        cout << "[" << id << "] permission granted to TAKEOFF. Taking off now...\n";
        // simulate takeoff time...
        cout << "[" << id << "] took off and cleared runway.\n";
        atc->runwayVacated();
    }
};

// ---------------- Concrete Mediator ----------------
class ControlTower : public ATCMediator {
private:
    vector<Aircraft*> registered;       // for reference (not strictly required)
    queue<Aircraft*> landingQueue;      // landing has higher priority generally
    queue<Aircraft*> takeoffQueue;
    bool runwayFree;

    // Helper: grant runway to one aircraft (landing preferred)
    void grantNext() {
        if (!runwayFree) return; // runway already occupied
        // Emergency handled separately (we assume emergency plane was immediately granted)
        if (!landingQueue.empty()) {
            Aircraft* plane = landingQueue.front();
            landingQueue.pop();
            runwayFree = false;
            cout << "[ATC] Granting landing permission to " << plane->getId() << endl;
            plane->land();
            return;
        }
        if (!takeoffQueue.empty()) {
            Aircraft* plane = takeoffQueue.front();
            takeoffQueue.pop();
            runwayFree = false;
            cout << "[ATC] Granting takeoff permission to " << plane->getId() << endl;
            plane->takeoff();
            return;
        }
        // nothing waiting
        cout << "[ATC] Runway is free; no pending requests.\n";
    }

public:
    ControlTower() : runwayFree(true) {}

    void registerAircraft(Aircraft* plane) override {
        registered.push_back(plane);
        cout << "[ATC] Registered aircraft: " << plane->getId() << endl;
    }

    void requestLanding(Aircraft* plane) override {
        // landing has priority; if runway free, grant immediately
        if (runwayFree && landingQueue.empty()) {
            runwayFree = false;
            cout << "[ATC] Runway free. Granting immediate landing to " << plane->getId() << endl;
            plane->land();
        } else {
            landingQueue.push(plane);
            cout << "[ATC] Runway busy. " << plane->getId() << " queued for landing. Position in queue: "
                 << landingQueue.size() << endl;
        }
    }

    void requestTakeoff(Aircraft* plane) override {
        // takeoff only when no landing planes waiting (landing prioritized)
        if (runwayFree && landingQueue.empty() && takeoffQueue.empty()) {
            runwayFree = false;
            cout << "[ATC] Runway free. Granting immediate takeoff to " << plane->getId() << endl;
            plane->takeoff();
        } else {
            takeoffQueue.push(plane);
            cout << "[ATC] Runway busy or landing queue exists. " << plane->getId() 
                 << " queued for takeoff. Position in queue: " << takeoffQueue.size() << endl;
        }
    }

    void notifyEmergency(Aircraft* plane) override {
        cout << "[ATC] EMERGENCY declared by " << plane->getId() << "! Preempting queues.\n";
        // If runway free, let it land immediately
        if (runwayFree) {
            runwayFree = false;
            cout << "[ATC] Runway free. Granting immediate emergency landing to " << plane->getId() << endl;
            plane->land();
            return;
        }
        // If runway occupied, we simulate prioritizing emergency: push to front of landing queue
        // We cannot really insert at front of std::queue; use vector transfer to rebuild with emergency first.
        // Simpler approach: rebuild landingQueue with emergency at front.
        vector<Aircraft*> temp;
        temp.push_back(plane); // emergency first
        while (!landingQueue.empty()) { temp.push_back(landingQueue.front()); landingQueue.pop(); }
        for (auto &p : temp) landingQueue.push(p);
        cout << "[ATC] " << plane->getId() << " placed at front of landing queue.\n";
    }

    // Called by aircraft when it clears the runway
    void runwayVacated() override {
        cout << "[ATC] Runway vacated.\n";
        runwayFree = true;
        // Grant next waiting plane (if any)
        grantNext();
    }
};

// ---------------- Client (simulation) ----------------
int main() {
    ControlTower tower;

    Aircraft a1("Flight-A1", &tower);
    Aircraft a2("Flight-B2", &tower);
    Aircraft a3("Flight-C3", &tower);
    Aircraft a4("Flight-D4", &tower);

    // Scenario:
    // - A1 requests landing (should get immediate permission)
    // - B2 requests landing (queued)
    // - C3 requests takeoff (queued because B2 waiting)
    // - D4 requests landing (queued behind B2)
    // - Then C3 declares emergency -> preempt and land ASAP
    cout << "\n--- Simulation start ---\n\n";

    a1.requestLanding(); // immediate
    a2.requestLanding(); // queued
    a3.requestTakeoff(); // queued (landing queue not empty)
    a4.requestLanding(); // queued

    cout << "\n-- Emergency incoming --\n";
    a3.declareEmergency(); // emergency by plane that was in takeoff queue

    cout << "\n--- Simulation ends after processing queue ---\n";
    return 0;
}
