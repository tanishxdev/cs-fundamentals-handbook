#include <bits/stdc++.h>
using namespace std;

// class for baking bread (only baking job)
class BreadBaker {
public:
    void bakeBread() {
        cout << "Baking bread..." << endl;
    }
};

// class for managing inventory (only inventory job)
class InventoryManager {
public:
    void manageInventory() {
        cout << "Managing inventory..." << endl;
    }
};

// class for ordering supplies (only ordering job)
class SupplyOrderer {
public:
    void orderSupplies() {
        cout << "Ordering supplies..." << endl;
    }
};
// class for serving customers (only customer service job)
class CustomerService {
public:
    void serveCustomer() {
        std::cout << "Serving customers..." << std::endl;
    }
};

// class for cleaning bakery (only cleaning job)
class BakeryCleaner {
public:
    void cleanBakery() {
        std::cout << "Cleaning the bakery..." << std::endl;
    }
};
int main()
{
    // each object has a single job/responsibility
    BreadBaker baker;
    InventoryManager inventoryManager;
    SupplyOrderer supplyOrderer;
    CustomerService customerService;
    BakeryCleaner bakeryCleaner;

    // call their specific responsibilities
    baker.bakeBread();
    inventoryManager.manageInventory();
    supplyOrderer.orderSupplies();
    customerService.serveCustomer();
    bakeryCleaner.cleanBakery();


    return 0;
}
/*
In the above example:

BreadBaker Class: Responsible solely for baking bread. This class focuses on ensuring the quality and standards of the bread without being burdened by other tasks.
InventoryManager Class: Handles inventory management, ensuring that the bakery has the right ingredients and supplies available.
SupplyOrder Class: Manages ordering supplies, ensuring that the bakery is stocked with necessary items.
CustomerService Class: Takes care of serving customers, providing a focused approach to customer interactions.
BakeryCleaner Class: Responsible for cleaning the bakery, ensuring a hygienic environment.

*/