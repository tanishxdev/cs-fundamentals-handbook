#include <iostream>
using namespace std;

// Forward declaration
class State;

// Context
class TrafficLight {
private:
    State* currentState;
public:
    TrafficLight(State* state) : currentState(state) {}
    void setState(State* state) { currentState = state; }
    void request();
};

// State Interface
class State {
public:
    virtual void handle(TrafficLight* light) = 0;
    virtual ~State() {}
};

// Concrete States
class RedState : public State {
public:
    void handle(TrafficLight* light) override;
};
class GreenState : public State {
public:
    void handle(TrafficLight* light) override;
};
class YellowState : public State {
public:
    void handle(TrafficLight* light) override;
};

// Define transitions
void RedState::handle(TrafficLight* light) {
    cout << "Red Light: STOP!\n";
    light->setState(new GreenState());
}
void GreenState::handle(TrafficLight* light) {
    cout << "Green Light: GO!\n";
    light->setState(new YellowState());
}
void YellowState::handle(TrafficLight* light) {
    cout << "Yellow Light: SLOW DOWN!\n";
    light->setState(new RedState());
}

// Context implementation
void TrafficLight::request() {
    currentState->handle(this);
}

// Client
int main() {
    TrafficLight light(new RedState());

    // Simulate multiple changes
    for (int i = 0; i < 5; i++) {
        light.request();
    }

    return 0;
}

// Real-world use:

// Traffic lights cycle between Red → Green → Yellow → Red..., and each state has its own behavior.