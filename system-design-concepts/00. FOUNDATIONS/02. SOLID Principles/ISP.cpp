#include <iostream>
#include <vector>
#include <string>

// Interface for vegetarian menu
class IVegetarianMenu {
public:
    virtual std::vector<std::string> getVegetarianItems() = 0;
    virtual ~IVegetarianMenu() = default;
};

// Interface for non-vegetarian menu
class INonVegetarianMenu {
public:
    virtual std::vector<std::string> getNonVegetarianItems() = 0;
    virtual ~INonVegetarianMenu() = default;
};

// Interface for drinks menu
class IDrinkMenu {
public:
    virtual std::vector<std::string> getDrinkItems() = 0;
    virtual ~IDrinkMenu() = default;
};

// Class for vegetarian menu
class VegetarianMenu : public IVegetarianMenu {
public:
    std::vector<std::string> getVegetarianItems() override {
        return {"Vegetable Curry", "Paneer Tikka", "Salad"};
    }
};

// Class for non-vegetarian menu
class NonVegetarianMenu : public INonVegetarianMenu {
public:
    std::vector<std::string> getNonVegetarianItems() override {
        return {"Chicken Curry", "Fish Fry", "Mutton Biryani"};
    }
};

// Class for drinks menu
class DrinkMenu : public IDrinkMenu {
public:
    std::vector<std::string> getDrinkItems() override {
        return {"Water", "Soda", "Juice"};
    }
};

// Function to display vegetarian menu
void displayVegetarianMenu(IVegetarianMenu* menu) {
    std::cout << "Vegetarian Menu:\n";
    for (const auto& item : menu->getVegetarianItems()) {
        std::cout << "- " << item << std::endl;
    }
}

// Function to display non-vegetarian menu
void displayNonVegetarianMenu(INonVegetarianMenu* menu) {
    std::cout << "Non-Vegetarian Menu:\n";
    for (const auto& item : menu->getNonVegetarianItems()) {
        std::cout << "- " << item << std::endl;
    }
}

int main() {
    VegetarianMenu vegMenu;
    NonVegetarianMenu nonVegMenu;
    DrinkMenu drinkMenu;

    displayVegetarianMenu(&vegMenu);
    displayNonVegetarianMenu(&nonVegMenu);

    return 0;
}

/*

NOTE : 

## 1. **What you tried (`IDrinkMenu(&IDrinkMenu);`)**

* Looks like you are trying to **create an object of interface type** (`IDrinkMenu`).
* But in C++, you **cannot directly create objects of abstract classes**.
* Reason: An abstract class has at least **one pure virtual function** (`=0`), which means its implementation is incomplete.

👉 Example:

```cpp
IDrinkMenu drink;  // ❌ Error: abstract class cannot be instantiated
```

This is why you can’t write `IDrinkMenu(&IDrinkMenu)` — it doesn’t make sense because C++ won’t let you create an abstract class object.

---

## 2. **Correct Way**

You should instead create an object of a **concrete class** (like `DrinkMenu`) that **implements `IDrinkMenu`**:

```cpp
DrinkMenu drinkMenu;         // ✅ Concrete class object
IDrinkMenu* menu = &drinkMenu; // ✅ Pointer to interface
```

Now, `menu` points to an object of type `DrinkMenu`, but from the client’s perspective it only knows the **interface contract** (`IDrinkMenu`).

---

## 3. **Why this design?**

* Interfaces (`IDrinkMenu`, `IVegetarianMenu`, etc.) are just **contracts**.
* They say *“whoever implements me must provide these methods.”*
* But the actual behavior lives in **concrete classes** (`DrinkMenu`, `VegetarianMenu`, etc.).
* This keeps code **flexible and decoupled**.

---

## 4. **Example**

```cpp
int main() {
    DrinkMenu drinkMenu;      // Concrete class
    IDrinkMenu* menu = &drinkMenu;  // Interface pointer points to concrete object

    for (auto item : menu->getDrinkItems()) {
        std::cout << item << std::endl;
    }

    return 0;
}
```

Output:

```
Water
Soda
Juice
```

---

✅ So the rule is:

* **You cannot instantiate an interface (abstract class).**
* You must **instantiate a concrete class** that implements the interface.
* Then you can use an **interface pointer or reference** to interact with it.

*/
