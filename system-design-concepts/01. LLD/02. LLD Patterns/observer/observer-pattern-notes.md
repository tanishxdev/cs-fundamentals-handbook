# Observer Design Pattern: Stepwise Explanation

## 1. What is Observer Design Pattern?


The **Observer Pattern** is a **behavioral design pattern** that defines a **one-to-many dependency** between objects:

* A **Subject** maintains some data or state.
* Multiple **Observers** depend on the subject.
* When the **subject’s state changes**, all registered observers are **automatically notified** and updated.

**Key idea:** Observers do not need to constantly check the subject—they get notified automatically.

---

## 2. Why Use Observer Pattern?

Without this pattern:

* Components dependent on a subject must **directly reference it**, creating **tight coupling**.
* Adding or removing observers requires **modifying the subject**, making code hard to maintain.
* State updates may not propagate consistently or efficiently.

**With Observer Pattern:**

* Observers can **register/unregister dynamically**.
* Subject does not need to know the details of observers (loose coupling).
* System becomes **flexible, maintainable, and scalable**.

---

## 3. Real-Life Analogy

**Example:** Weather Station

* **Subject:** Weather Station maintains current weather data.
* **Observers:** Mobile apps, TVs, smartwatches.
* **Behavior:** Whenever the weather changes, all observers get updated automatically.

This allows new observers to be added or removed **without changing the weather station code**.

---

## 4. Problem It Solves

Example scenario: Weather monitoring system

* Multiple devices need updates when weather changes.
* Without Observer pattern:

  * Each device must query the station manually.
  * Adding/removing devices requires changes in weather station code.
  * Tight coupling occurs between devices and weather station.

**Solution:** Use Observer Pattern to **decouple the weather station from devices**.

---

## 5. Components

| Component            | Role                                                                      |
| -------------------- | ------------------------------------------------------------------------- |
| **Subject**          | Maintains observers and notifies them of changes.                         |
| **Observer**         | Interface defining `update()` method for receiving updates.               |
| **ConcreteSubject**  | Implements Subject, holds state, and notifies observers (WeatherStation). |
| **ConcreteObserver** | Implements Observer, reacts to updates (PhoneDisplay, TVDisplay).         |
| **Client**           | Registers/unregisters observers and triggers updates.                     |

---

## 6. Logic / Flow

1. Observers **register** with the subject.
2. Subject maintains a **list of observers**.
3. When the subject’s state changes, it **notifies all observers** by calling their `update()` method.
4. Observers **update themselves** based on the new state.
5. Observers can be **added or removed dynamically** without modifying the subject.

---

## 7. C++ Implementation


### Step 1: Observer Interface

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Observer {
public:
    virtual void update(const string& weather) = 0;
    virtual ~Observer() {}
};
```

* Defines the **common interface** for all observers.
* Each observer implements `update()`.

---

### Step 2: Subject Interface

```cpp
class Subject {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};
```

* Provides methods to **manage observers** and **notify them**.

---

### Step 3: Concrete Subject

```cpp
class WeatherStation : public Subject {
private:
    vector<Observer*> observers;
    string weather;

public:
    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(weather);
        }
    }

    void setWeather(const string& newWeather) {
        weather = newWeather;
        notifyObservers();
    }
};
```

* Maintains a list of observers.
* Notifies all observers whenever weather changes.

---

### Step 4: Concrete Observers

```cpp
class PhoneDisplay : public Observer {
private:
    string weather;

    void display() {
        cout << "Phone Display: Weather updated - " << weather << endl;
    }

public:
    void update(const string& weather) override {
        this->weather = weather;
        display();
    }
};

class TVDisplay : public Observer {
private:
    string weather;

    void display() {
        cout << "TV Display: Weather updated - " << weather << endl;
    }

public:
    void update(const string& weather) override {
        this->weather = weather;
        display();
    }
};
```

* Each observer **reacts to updates** and displays the new weather.

---

### Step 5: Client / Usage

```cpp
int main() {
    WeatherStation weatherStation;

    PhoneDisplay phoneDisplay;
    TVDisplay tvDisplay;

    // Register observers
    weatherStation.addObserver(&phoneDisplay);
    weatherStation.addObserver(&tvDisplay);

    // Simulate weather changes
    weatherStation.setWeather("Sunny");
    weatherStation.setWeather("Rainy");
    weatherStation.setWeather("Cloudy");

    // Remove one observer
    weatherStation.removeObserver(&tvDisplay);

    // Notify remaining observer
    weatherStation.setWeather("Windy");

    return 0;
}
```

✅ **Output:**

```
Phone Display: Weather updated - Sunny
TV Display: Weather updated - Sunny
Phone Display: Weather updated - Rainy
TV Display: Weather updated - Rainy
Phone Display: Weather updated - Cloudy
TV Display: Weather updated - Cloudy
Phone Display: Weather updated - Windy
```

---

## 8. Benefits of Observer Pattern

* **Loose Coupling:** Subject doesn’t know details of observers.
* **Dynamic Relationships:** Observers can be added/removed at runtime.
* **Automatic Updates:** All observers are synchronized with subject state.
* **Scalability:** Works well with multiple observers.
* **Flexibility:** Supports one-to-many relationships.

