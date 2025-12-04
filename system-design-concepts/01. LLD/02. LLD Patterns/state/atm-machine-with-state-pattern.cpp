#include <iostream>
using namespace std;

class ATMState; // Forward declaration

// Context Class
class ATMMachine {
private:
    ATMState* state;
    int cashInMachine;
public:
    ATMMachine(int cash);
    void setState(ATMState* s) { state = s; }
    int getCash() { return cashInMachine; }
    void setCash(int cash) { cashInMachine = cash; }
    void insertCard();
    void ejectCard();
    void enterPin(int pin);
    void requestCash(int amount);
};

// State Interface
class ATMState {
public:
    virtual void insertCard(ATMMachine* atm) = 0;
    virtual void ejectCard(ATMMachine* atm) = 0;
    virtual void enterPin(ATMMachine* atm, int pin) = 0;
    virtual void requestCash(ATMMachine* atm, int amount) = 0;
    virtual ~ATMState() {}
};

// Forward declare concrete states
class NoCardState;
class HasCardState;
class CorrectPinState;
class NoCashState;

// ---------------- Concrete States ----------------

// No Card
class NoCardState : public ATMState {
public:
    void insertCard(ATMMachine* atm) override;
    void ejectCard(ATMMachine* atm) override { cout << "No card to eject.\n"; }
    void enterPin(ATMMachine* atm, int pin) override { cout << "Insert card first.\n"; }
    void requestCash(ATMMachine* atm, int amount) override { cout << "Insert card first.\n"; }
};

// Has Card
class HasCardState : public ATMState {
public:
    void insertCard(ATMMachine* atm) override { cout << "Card already inserted.\n"; }
    void ejectCard(ATMMachine* atm) override;
    void enterPin(ATMMachine* atm, int pin) override;
    void requestCash(ATMMachine* atm, int amount) override { cout << "Enter PIN first.\n"; }
};

// Correct Pin
class CorrectPinState : public ATMState {
public:
    void insertCard(ATMMachine* atm) override { cout << "Card already inserted.\n"; }
    void ejectCard(ATMMachine* atm) override;
    void enterPin(ATMMachine* atm, int pin) override { cout << "PIN already entered.\n"; }
    void requestCash(ATMMachine* atm, int amount) override;
};

// No Cash
class NoCashState : public ATMState {
public:
    void insertCard(ATMMachine* atm) override { cout << "ATM has no cash. Out of service.\n"; }
    void ejectCard(ATMMachine* atm) override { cout << "No card to eject.\n"; }
    void enterPin(ATMMachine* atm, int pin) override { cout << "ATM has no cash.\n"; }
    void requestCash(ATMMachine* atm, int amount) override { cout << "ATM has no cash.\n"; }
};

// ---------------- State Transitions ----------------

// NoCard → HasCard
void NoCardState::insertCard(ATMMachine* atm) {
    cout << "Card inserted. Please enter your PIN.\n";
    atm->setState(new HasCardState());
}

// HasCard → NoCard
void HasCardState::ejectCard(ATMMachine* atm) {
    cout << "Card ejected.\n";
    atm->setState(new NoCardState());
}

// HasCard → CorrectPin (if correct PIN)
void HasCardState::enterPin(ATMMachine* atm, int pin) {
    if (pin == 1234) {
        cout << "PIN correct. You can request cash.\n";
        atm->setState(new CorrectPinState());
    } else {
        cout << "Wrong PIN. Card ejected.\n";
        atm->setState(new NoCardState());
    }
}

// CorrectPin → RequestCash
void CorrectPinState::requestCash(ATMMachine* atm, int amount) {
    if (amount <= atm->getCash()) {
        cout << "Dispensing " << amount << " cash.\n";
        atm->setCash(atm->getCash() - amount);

        if (atm->getCash() > 0) {
            atm->setState(new NoCardState());
            cout << "Card ejected.\n";
        } else {
            atm->setState(new NoCashState());
            cout << "ATM is now out of cash!\n";
        }
    } else {
        cout << "Not enough cash in ATM.\n";
        atm->setState(new NoCardState());
    }
}

// CorrectPin → Eject Card
void CorrectPinState::ejectCard(ATMMachine* atm) {
    cout << "Card ejected.\n";
    atm->setState(new NoCardState());
}

// ---------------- ATMMachine Implementation ----------------
ATMMachine::ATMMachine(int cash) : cashInMachine(cash) {
    if (cash > 0)
        state = new NoCardState();
    else
        state = new NoCashState();
}

void ATMMachine::insertCard() { state->insertCard(this); }
void ATMMachine::ejectCard() { state->ejectCard(this); }
void ATMMachine::enterPin(int pin) { state->enterPin(this, pin); }
void ATMMachine::requestCash(int amount) { state->requestCash(this, amount); }

// ---------------- Client ----------------
int main() {
    ATMMachine atm(2000); // ATM with 2000 cash

    atm.insertCard();
    atm.enterPin(1234);
    atm.requestCash(1000);

    atm.insertCard();
    atm.enterPin(1234);
    atm.requestCash(1500); // More than remaining

    atm.insertCard(); // ATM may go out of cash here

    return 0;
}

// Real-world use:

// ATM behaves differently depending on state:

// NoCard → ask to insert card

// HasCard → ask for PIN

// CorrectPin → allow transaction

// NoCash → show "Out of Service"

// 👉 (More complex, but shows real-world relevance.)