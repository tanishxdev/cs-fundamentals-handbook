#include <iostream>
#include <string>
using namespace std;

//
// 🧱 Step 1: Product Class — House
//
class House {
private:
    string foundation;
    string structure;
    string roof;
    string interior;

public:
    void setFoundation(string f) { foundation = f; }
    void setStructure(string s) { structure = s; }
    void setRoof(string r) { roof = r; }
    void setInterior(string i) { interior = i; }

    void showDetails() {
        cout << "\n🏠 House Configuration:\n";
        cout << "Foundation: " << foundation << endl;
        cout << "Structure : " << structure << endl;
        cout << "Roof      : " << roof << endl;
        cout << "Interior  : " << interior << endl;
    }
};

//
// ⚙️ Step 2: Builder Interface
//
class HouseBuilder {
public:
    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual void buildInterior() = 0;
    virtual House* getHouse() = 0;
    virtual ~HouseBuilder() {}
};

//
// 🧰 Step 3: Concrete Builders
//

// 🏡 Normal House Builder
class NormalHouseBuilder : public HouseBuilder {
private:
    House* house;
public:
    NormalHouseBuilder() { house = new House(); }

    void buildFoundation() override { house->setFoundation("Concrete Foundation"); }
    void buildStructure() override { house->setStructure("Brick Walls"); }
    void buildRoof() override { house->setRoof("Concrete Roof"); }
    void buildInterior() override { house->setInterior("Basic Interior"); }

    House* getHouse() override { return house; }
};

// 🏰 Luxury House Builder
class LuxuryHouseBuilder : public HouseBuilder {
private:
    House* house;
public:
    LuxuryHouseBuilder() { house = new House(); }

    void buildFoundation() override { house->setFoundation("Reinforced Steel Foundation"); }
    void buildStructure() override { house->setStructure("Marble Walls"); }
    void buildRoof() override { house->setRoof("Glass Roof with Skylight"); }
    void buildInterior() override { house->setInterior("Luxury Interior with Smart Home Features"); }

    House* getHouse() override { return house; }
};

//
// 👷 Step 4: Director — Civil Engineer
//
class CivilEngineer {
private:
    HouseBuilder* builder;
public:
    CivilEngineer(HouseBuilder* b) : builder(b) {}

    void constructHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
    }

    House* getHouse() {
        return builder->getHouse();
    }
};

//
// 🧠 Step 5: Client Code
//
int main() {
    cout << "=== 🏗️ Building Different Types of Houses ===\n";

    // Build a normal house
    NormalHouseBuilder normalBuilder;
    CivilEngineer engineer1(&normalBuilder);
    engineer1.constructHouse();
    House* normalHouse = engineer1.getHouse();
    normalHouse->showDetails();

    // Build a luxury house
    LuxuryHouseBuilder luxuryBuilder;
    CivilEngineer engineer2(&luxuryBuilder);
    engineer2.constructHouse();
    House* luxuryHouse = engineer2.getHouse();
    luxuryHouse->showDetails();

    return 0;
}
