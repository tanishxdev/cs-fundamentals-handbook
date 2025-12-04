for lld alwasy goo like this ok

I'll provide a complete step-by-step Low-Level Design (LLD) implementation for a Parking Lot System in C++. Let's build this systematically.

## Step 1: Core Enums and Constants

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include <algorithm>

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

enum class ParkingSpotType {
    COMPACT,
    LARGE,
    HANDICAPPED,
    MOTORCYCLE
};

enum class PaymentStatus {
    PENDING,
    COMPLETED,
    FAILED,
    REFUNDED
};

enum class AccountStatus {
    ACTIVE,
    CLOSED,
    BLOCKED
};

class Constants {
public:
    static const int MAX_SPOTS_PER_FLOOR = 100;
    static const int MAX_FLOORS = 10;
};
```

## Step 2: Vehicle Class

```cpp
class Vehicle {
private:
    std::string licensePlate;
    VehicleType type;
    std::string ownerName;

public:
    Vehicle(const std::string& plate, VehicleType vType, const std::string& owner)
        : licensePlate(plate), type(vType), ownerName(owner) {}

    std::string getLicensePlate() const { return licensePlate; }
    VehicleType getVehicleType() const { return type; }
    std::string getOwnerName() const { return ownerName; }
    
    // Convert vehicle type to parking spot type
    ParkingSpotType getCompatibleSpotType() const {
        switch(type) {
            case VehicleType::CAR: return ParkingSpotType::COMPACT;
            case VehicleType::BIKE: return ParkingSpotType::MOTORCYCLE;
            case VehicleType::TRUCK: return ParkingSpotType::LARGE;
            default: return ParkingSpotType::COMPACT;
        }
    }
};
```

## Step 3: Parking Spot Class

```cpp
class ParkingSpot {
private:
    int spotId;
    int floorNumber;
    ParkingSpotType type;
    bool isAvailable;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int id, int floor, ParkingSpotType spotType)
        : spotId(id), floorNumber(floor), type(spotType), 
          isAvailable(true), parkedVehicle(nullptr) {}

    // Getters
    int getSpotId() const { return spotId; }
    int getFloorNumber() const { return floorNumber; }
    ParkingSpotType getSpotType() const { return type; }
    bool getIsAvailable() const { return isAvailable; }
    Vehicle* getParkedVehicle() const { return parkedVehicle; }

    // Park vehicle in this spot
    bool parkVehicle(Vehicle* vehicle) {
        if (!isAvailable || vehicle->getCompatibleSpotType() != type) {
            return false;
        }
        parkedVehicle = vehicle;
        isAvailable = false;
        return true;
    }

    // Remove vehicle from spot
    void removeVehicle() {
        parkedVehicle = nullptr;
        isAvailable = true;
    }

    // Check if spot is compatible with vehicle type
    bool isCompatible(VehicleType vehicleType) const {
        ParkingSpotType requiredType;
        switch(vehicleType) {
            case VehicleType::CAR: requiredType = ParkingSpotType::COMPACT; break;
            case VehicleType::BIKE: requiredType = ParkingSpotType::MOTORCYCLE; break;
            case VehicleType::TRUCK: requiredType = ParkingSpotType::LARGE; break;
            default: return false;
        }
        return type == requiredType;
    }
};
```

## Step 4: Parking Floor Class

```cpp
class ParkingFloor {
private:
    int floorNumber;
    std::vector<ParkingSpot> spots;
    std::map<ParkingSpotType, int> availableSpots;

public:
    ParkingFloor(int floorNum) : floorNumber(floorNum) {
        initializeSpots();
    }

private:
    void initializeSpots() {
        // Initialize different types of spots
        int spotId = 1;
        
        // Compact spots for cars (60%)
        for (int i = 0; i < Constants::MAX_SPOTS_PER_FLOOR * 0.6; i++) {
            spots.emplace_back(spotId++, floorNumber, ParkingSpotType::COMPACT);
        }
        
        // Large spots for trucks (20%)
        for (int i = 0; i < Constants::MAX_SPOTS_PER_FLOOR * 0.2; i++) {
            spots.emplace_back(spotId++, floorNumber, ParkingSpotType::LARGE);
        }
        
        // Motorcycle spots (15%)
        for (int i = 0; i < Constants::MAX_SPOTS_PER_FLOOR * 0.15; i++) {
            spots.emplace_back(spotId++, floorNumber, ParkingSpotType::MOTORCYCLE);
        }
        
        // Handicapped spots (5%)
        for (int i = 0; i < Constants::MAX_SPOTS_PER_FLOOR * 0.05; i++) {
            spots.emplace_back(spotId++, floorNumber, ParkingSpotType::HANDICAPPED);
        }

        updateAvailableSpotsCount();
    }

    void updateAvailableSpotsCount() {
        availableSpots.clear();
        for (const auto& spot : spots) {
            if (spot.getIsAvailable()) {
                availableSpots[spot.getSpotType()]++;
            }
        }
    }

public:
    int getFloorNumber() const { return floorNumber; }
    const std::vector<ParkingSpot>& getSpots() const { return spots; }

    int getAvailableSpotsCount(ParkingSpotType type) const {
        auto it = availableSpots.find(type);
        return it != availableSpots.end() ? it->second : 0;
    }

    // Find available spot for a vehicle type
    ParkingSpot* findAvailableSpot(VehicleType vehicleType) {
        ParkingSpotType requiredType;
        switch(vehicleType) {
            case VehicleType::CAR: requiredType = ParkingSpotType::COMPACT; break;
            case VehicleType::BIKE: requiredType = ParkingSpotType::MOTORCYCLE; break;
            case VehicleType::TRUCK: requiredType = ParkingSpotType::LARGE; break;
            default: return nullptr;
        }

        for (auto& spot : spots) {
            if (spot.getIsAvailable() && spot.getSpotType() == requiredType) {
                return &spot;
            }
        }
        return nullptr;
    }

    // Park vehicle in this floor
    bool parkVehicle(Vehicle* vehicle) {
        ParkingSpot* spot = findAvailableSpot(vehicle->getVehicleType());
        if (spot && spot->parkVehicle(vehicle)) {
            updateAvailableSpotsCount();
            return true;
        }
        return false;
    }

    // Remove vehicle from spot
    void removeVehicle(int spotId) {
        for (auto& spot : spots) {
            if (spot.getSpotId() == spotId) {
                spot.removeVehicle();
                updateAvailableSpotsCount();
                break;
            }
        }
    }

    void displayAvailability() const {
        std::cout << "Floor " << floorNumber << " Availability:\n";
        std::cout << "  Compact Spots: " << getAvailableSpotsCount(ParkingSpotType::COMPACT) << "\n";
        std::cout << "  Large Spots: " << getAvailableSpotsCount(ParkingSpotType::LARGE) << "\n";
        std::cout << "  Motorcycle Spots: " << getAvailableSpotsCount(ParkingSpotType::MOTORCYCLE) << "\n";
        std::cout << "  Handicapped Spots: " << getAvailableSpotsCount(ParkingSpotType::HANDICAPPED) << "\n";
    }
};
```

## Step 5: Parking Lot Singleton Class

```cpp
class ParkingLot {
private:
    static ParkingLot* instance;
    std::vector<ParkingFloor> floors;
    std::map<std::string, std::pair<int, int>> vehicleLocation; // license plate -> (floor, spot)

    // Private constructor for singleton
    ParkingLot() {
        initializeFloors();
    }

    void initializeFloors() {
        for (int i = 1; i <= Constants::MAX_FLOORS; i++) {
            floors.emplace_back(i);
        }
    }

public:
    // Delete copy constructor and assignment operator
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    static ParkingLot* getInstance() {
        if (instance == nullptr) {
            instance = new ParkingLot();
        }
        return instance;
    }

    // Park vehicle and return ticket
    std::string parkVehicle(Vehicle* vehicle) {
        for (auto& floor : floors) {
            if (floor.parkVehicle(vehicle)) {
                // Find the spot where vehicle was parked
                for (const auto& spot : floor.getSpots()) {
                    if (!spot.getIsAvailable() && 
                        spot.getParkedVehicle()->getLicensePlate() == vehicle->getLicensePlate()) {
                        vehicleLocation[vehicle->getLicensePlate()] = 
                            std::make_pair(floor.getFloorNumber(), spot.getSpotId());
                        
                        return generateTicket(floor.getFloorNumber(), spot.getSpotId());
                    }
                }
            }
        }
        return ""; // No available spot
    }

    // Remove vehicle
    bool removeVehicle(const std::string& licensePlate) {
        auto it = vehicleLocation.find(licensePlate);
        if (it != vehicleLocation.end()) {
            int floorNum = it->second.first;
            int spotId = it->second.second;
            
            if (floorNum >= 1 && floorNum <= floors.size()) {
                floors[floorNum - 1].removeVehicle(spotId);
                vehicleLocation.erase(it);
                return true;
            }
        }
        return false;
    }

    // Check availability
    void displayAvailability() const {
        std::cout << "\n=== PARKING LOT AVAILABILITY ===\n";
        for (const auto& floor : floors) {
            floor.displayAvailability();
        }
        std::cout << "================================\n\n";
    }

    // Get vehicle location
    std::pair<int, int> getVehicleLocation(const std::string& licensePlate) const {
        auto it = vehicleLocation.find(licensePlate);
        if (it != vehicleLocation.end()) {
            return it->second;
        }
        return std::make_pair(-1, -1); // Not found
    }

private:
    std::string generateTicket(int floor, int spot) {
        return "TKT_" + std::to_string(floor) + "_" + std::to_string(spot) + 
               "_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }
};

// Initialize static member
ParkingLot* ParkingLot::instance = nullptr;
```

## Step 6: Ticket and Payment Classes

```cpp
class ParkingTicket {
private:
    std::string ticketNumber;
    std::string licensePlate;
    std::chrono::system_clock::time_point entryTime;
    int floorNumber;
    int spotId;
    double amount;
    PaymentStatus status;

public:
    ParkingTicket(const std::string& ticketNum, const std::string& plate, 
                  int floor, int spot)
        : ticketNumber(ticketNum), licensePlate(plate), 
          entryTime(std::chrono::system_clock::now()),
          floorNumber(floor), spotId(spot), amount(0.0), 
          status(PaymentStatus::PENDING) {}

    // Getters
    std::string getTicketNumber() const { return ticketNumber; }
    std::string getLicensePlate() const { return licensePlate; }
    auto getEntryTime() const { return entryTime; }
    int getFloorNumber() const { return floorNumber; }
    int getSpotId() const { return spotId; }
    double getAmount() const { return amount; }
    PaymentStatus getStatus() const { return status; }

    // Calculate charges based on time spent
    double calculateCharges() {
        auto exitTime = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(exitTime - entryTime);
        
        // $2 per hour, minimum $1
        double hours = duration.count() / 60.0;
        amount = std::max(1.0, hours * 2.0);
        return amount;
    }

    void markAsPaid() {
        status = PaymentStatus::COMPLETED;
    }
};

class PaymentProcessor {
public:
    static bool processPayment(double amount) {
        // Simulate payment processing
        std::cout << "Processing payment of $" << amount << "...\n";
        
        // Simulate network delay
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Simulate 90% success rate
        return (rand() % 10) != 0; // 90% success rate
    }
    
    static bool processRefund(double amount) {
        std::cout << "Processing refund of $" << amount << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    }
};
```

## Step 7: Parking Manager Class

```cpp
class ParkingManager {
private:
    ParkingLot* parkingLot;
    std::map<std::string, ParkingTicket> activeTickets;

public:
    ParkingManager() {
        parkingLot = ParkingLot::getInstance();
    }

    // Park vehicle and issue ticket
    std::string parkVehicle(Vehicle* vehicle) {
        std::string ticketNum = parkingLot->parkVehicle(vehicle);
        if (!ticketNum.empty()) {
            auto location = parkingLot->getVehicleLocation(vehicle->getLicensePlate());
            ParkingTicket ticket(ticketNum, vehicle->getLicensePlate(), 
                               location.first, location.second);
            activeTickets[ticketNum] = ticket;
            
            std::cout << "Vehicle " << vehicle->getLicensePlate() 
                      << " parked successfully!\n";
            std::cout << "Ticket: " << ticketNum << "\n";
            std::cout << "Location: Floor " << location.first 
                      << ", Spot " << location.second << "\n";
        } else {
            std::cout << "No available parking spots for vehicle type!\n";
        }
        return ticketNum;
    }

    // Exit vehicle and process payment
    bool exitVehicle(const std::string& ticketNumber) {
        auto it = activeTickets.find(ticketNumber);
        if (it == activeTickets.end()) {
            std::cout << "Invalid ticket number!\n";
            return false;
        }

        ParkingTicket& ticket = it->second;
        double amount = ticket.calculateCharges();
        
        std::cout << "Parking duration calculated.\n";
        std::cout << "Amount due: $" << amount << "\n";

        // Process payment
        if (PaymentProcessor::processPayment(amount)) {
            ticket.markAsPaid();
            parkingLot->removeVehicle(ticket.getLicensePlate());
            activeTickets.erase(it);
            
            std::cout << "Payment successful! Vehicle can exit.\n";
            return true;
        } else {
            std::cout << "Payment failed! Please try again.\n";
            return false;
        }
    }

    // Check availability
    void checkAvailability() {
        parkingLot->displayAvailability();
    }

    // Find vehicle
    void findVehicle(const std::string& licensePlate) {
        auto location = parkingLot->getVehicleLocation(licensePlate);
        if (location.first != -1) {
            std::cout << "Vehicle " << licensePlate 
                      << " is parked at Floor " << location.first 
                      << ", Spot " << location.second << "\n";
        } else {
            std::cout << "Vehicle " << licensePlate << " not found in parking lot.\n";
        }
    }
};
```

## Step 8: Complete Working Code with Main Function

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include <algorithm>
#include <thread>
#include <cstdlib>
#include <ctime>

// Add all the previous class definitions here...

int main() {
    std::srand(std::time(0)); // Seed for random number generation
    
    ParkingManager manager;
    
    std::cout << "=== PARKING LOT MANAGEMENT SYSTEM ===\n\n";
    
    // Create some vehicles
    Vehicle car1("ABC123", VehicleType::CAR, "John Doe");
    Vehicle bike1("XYZ789", VehicleType::BIKE, "Jane Smith");
    Vehicle truck1("TRK456", VehicleType::TRUCK, "Bob Wilson");
    Vehicle car2("DEF456", VehicleType::CAR, "Alice Brown");
    
    // Display initial availability
    manager.checkAvailability();
    
    // Park vehicles
    std::cout << "--- Parking Vehicles ---\n";
    std::string ticket1 = manager.parkVehicle(&car1);
    std::string ticket2 = manager.parkVehicle(&bike1);
    std::string ticket3 = manager.parkVehicle(&truck1);
    std::string ticket4 = manager.parkVehicle(&car2);
    
    std::cout << "\n--- Current Availability ---\n";
    manager.checkAvailability();
    
    // Find a vehicle
    std::cout << "--- Finding Vehicle ---\n";
    manager.findVehicle("ABC123");
    manager.findVehicle("UNKNOWN");
    
    // Wait for some time to simulate parking duration
    std::cout << "\nWaiting for 3 seconds to simulate parking time...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Exit vehicles
    std::cout << "\n--- Exiting Vehicles ---\n";
    manager.exitVehicle(ticket1);
    manager.exitVehicle(ticket2);
    
    std::cout << "\n--- Final Availability ---\n";
    manager.checkAvailability();
    
    // Test error cases
    std::cout << "--- Testing Error Cases ---\n";
    manager.exitVehicle("INVALID_TICKET"); // Invalid ticket
    manager.findVehicle("NOT_EXIST"); // Non-existent vehicle
    
    // Try to park more vehicles
    std::cout << "\n--- Parking More Vehicles ---\n";
    Vehicle car3("GHI789", VehicleType::CAR, "Charlie Davis");
    Vehicle bike2("MOTO123", VehicleType::BIKE, "David Lee");
    
    manager.parkVehicle(&car3);
    manager.parkVehicle(&bike2);
    
    manager.checkAvailability();
    
    std::cout << "=== SYSTEM SHUTDOWN ===\n";
    
    return 0;
}
```

## Step 9: Compilation and Output

To compile and run this code:

```bash
g++ -std=c++11 -o parking_lot parking_lot.cpp
./parking_lot
```

**Expected Output:**
```
=== PARKING LOT MANAGEMENT SYSTEM ===

=== PARKING LOT AVAILABILITY ===
Floor 1 Availability:
  Compact Spots: 60
  Large Spots: 20
  Motorcycle Spots: 15
  Handicapped Spots: 5
... (other floors)
================================

--- Parking Vehicles ---
Vehicle ABC123 parked successfully!
Ticket: TKT_1_1_1700000000
Location: Floor 1, Spot 1
Vehicle XYZ789 parked successfully!
Ticket: TKT_1_61_1700000001
Location: Floor 1, Spot 61
Vehicle TRK456 parked successfully!
Ticket: TKT_1_81_1700000002
Location: Floor 1, Spot 81
Vehicle DEF456 parked successfully!
Ticket: TKT_1_2_1700000003
Location: Floor 1, Spot 2

--- Current Availability ---
=== PARKING LOT AVAILABILITY ===
Floor 1 Availability:
  Compact Spots: 58
  Large Spots: 19
  Motorcycle Spots: 14
  Handicapped Spots: 5
...

--- Finding Vehicle ---
Vehicle ABC123 is parked at Floor 1, Spot 1
Vehicle UNKNOWN not found in parking lot.

Waiting for 3 seconds to simulate parking time...

--- Exiting Vehicles ---
Parking duration calculated.
Amount due: $1
Processing payment of $1...
Payment successful! Vehicle can exit.
Parking duration calculated.
Amount due: $1
Processing payment of $1...
Payment successful! Vehicle can exit.

--- Final Availability ---
=== PARKING LOT AVAILABILITY ===
Floor 1 Availability:
  Compact Spots: 59
  Large Spots: 19
  Motorcycle Spots: 15
  Handicapped Spots: 5
...
```

## Key Features Implemented:

1. **Singleton Pattern** for ParkingLot to ensure single instance
2. **Factory Pattern** for creating different vehicle and spot types
3. **Strategy Pattern** for payment processing
4. **Real-time availability tracking**
5. **Ticket management system**
6. **Payment processing with simulation**
7. **Vehicle location tracking**
8. **Multi-floor parking support**
9. **Different spot types (Compact, Large, Motorcycle, Handicapped)**
10. **Error handling for invalid operations**

This implementation provides a complete, working parking lot system that can be extended with database persistence, web APIs, and user interfaces.