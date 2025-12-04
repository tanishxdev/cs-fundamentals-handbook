#include <iostream>

// Abstraction
class ILight {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~ILight() = default;
};

// Low-level module 1
class LEDLight : public ILight {
public:
    void turnOn() override { std::cout << "LED light is ON\n"; }
    void turnOff() override { std::cout << "LED light is OFF\n"; }
};

// Low-level module 2
class CFLBulb : public ILight {
public:
    void turnOn() override { std::cout << "CFL bulb is ON\n"; }
    void turnOff() override { std::cout << "CFL bulb is OFF\n"; }
};

// High-level module
class Switch {
private:
    ILight* light;    // Depends on abstraction
public:
    Switch(ILight* l) : light(l) {}
    void operate() {
        light->turnOn();
        std::cout << "Switch is operating the light\n";
    }
};

int main() {
    LEDLight led;
    CFLBulb cfl;

    // Switch using LED
    Switch s1(&led);
    s1.operate();

    // Switch using CFL
    Switch s2(&cfl);
    s2.operate();

    return 0;
}
