#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for std::remove
using namespace std;

// ---------------- Observer Pattern ---------------- //

// Observer Interface
class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
    virtual ~Observer() {}
};

// Subject Interface
class Subject {
public:
    virtual void addObserver(Observer* obs) = 0;
    virtual void removeObserver(Observer* obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};

// Concrete Subject: WeatherStation
class WeatherStation : public Subject {
private:
    vector<Observer*> observers;
    float temperature;
    float humidity;

public:
    void addObserver(Observer* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (auto* obs : observers) {
            obs->update(temperature, humidity);
        }
    }

    // Update weather data (this will trigger notifications)
    void setWeather(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        cout << "\n[WeatherStation] New weather data set: "
             << "Temp = " << temp << "°C, Humidity = " << hum << "%\n";
        notifyObservers();
    }
};

// Concrete Observer: Mobile App
class MobileApp : public Observer {
private:
    string appName;

public:
    MobileApp(string name) : appName(name) {}

    void update(float temperature, float humidity) override {
        cout << appName << " App: Weather Update -> Temp: "
             << temperature << "°C, Humidity: " << humidity << "%\n";
    }
};

// Concrete Observer: Website Display
class WebsiteDisplay : public Observer {
private:
    string siteName;

public:
    WebsiteDisplay(string name) : siteName(name) {}

    void update(float temperature, float humidity) override {
        cout << siteName << " Website: Weather Update -> Temp: "
             << temperature << "°C, Humidity: " << humidity << "%\n";
    }
};

// ---------------- Client ---------------- //
int main() {
    // Create Weather Station
    WeatherStation station;

    // Create Observers (Apps/Displays)
    MobileApp app1("AccuWeather");
    MobileApp app2("WeatherNow");
    WebsiteDisplay site("WeatherPortal");

    // Subscribe apps to weather station
    station.addObserver(&app1);
    station.addObserver(&app2);
    station.addObserver(&site);

    // Set new weather data (all observers will be notified)
    station.setWeather(30.5, 70.2);

    cout << "\n---- Later ----\n";

    // Remove one observer
    station.removeObserver(&app2);

    // Update weather again (only remaining observers notified)
    station.setWeather(25.8, 60.5);

    return 0;
}


// 🔑 Takeaways:

// WeatherStation acts as publisher.

// MobileApp and WebsiteDisplay act as subscribers.

// Whenever setWeather() is called, all subscribers automatically get updates.