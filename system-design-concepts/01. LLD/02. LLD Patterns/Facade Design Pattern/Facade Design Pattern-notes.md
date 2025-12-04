# Facade Design Pattern - Complete Guide

## The Problem: Complexity of Subsystems
![](https://media.geeksforgeeks.org/wp-content/uploads/20250909113721108916/Fcade.webp)

### The Real-World Complexity Problem

Imagine you're building a home theater system with multiple components:

- DVD Player
- Projector
- Surround Sound System
- Lights Controller
- Screen Controller

Without a facade, to watch a movie you'd need to:

```cpp
// Complex client code without facade
dvdPlayer.turnOn();
dvdPlayer.insertMovie("avatar");
projector.turnOn();
projector.setInput("DVD");
projector.setResolution("1080p");
soundSystem.turnOn();
soundSystem.setVolume(70);
soundSystem.setMode("surround");
lightsController.dimLights(30);
screenController.lowerScreen();
// ... and more steps
```

**Problems with this approach:**
1. **Complex Client Code**: Client needs to know all subsystem details
2. **Tight Coupling**: Client depends on multiple subsystems directly
3. **Error Prone**: Forgetting one step breaks the entire process
4. **Hard to Maintain**: Changes in subsystems affect all clients
5. **Violates Single Responsibility**: Client handles too many concerns

### Real-World Analogies

1. **Hotel Reception**: You don't deal with kitchen, housekeeping, billing separately
2. **Car Ignition**: One key turn starts engine, electronics, safety systems
3. **Bank Teller**: Single interface for accounts, loans, transactions

## The Solution: Facade Design Pattern
![](https://media.geeksforgeeks.org/wp-content/uploads/20240118172403/Component-of-Facade-Method-Design-Pattern.jpg)
### Core Concept

A facade provides a simplified interface to a complex subsystem. It doesn't add new functionality but makes existing functionality easier to use.

**Key Idea**: Create a "unified front door" to a set of interfaces in a subsystem.

## Step-by-Step Implementation

### Basic Structure

```
Complex Subsystem
    ↑
    |
Facade (Simplified Interface)
    ↑
    |
Client (Uses only Facade)
```

### 1. Subsystem Classes

The complex components that do the actual work:

```cpp
#include <iostream>
#include <string>
#include <memory>

// Subsystem: DVD Player
class DVDPlayer {
public:
    void turnOn() {
        std::cout << "DVD Player: Turning on" << std::endl;
    }
    
    void turnOff() {
        std::cout << "DVD Player: Turning off" << std::endl;
    }
    
    void playMovie(const std::string& movie) {
        std::cout << "DVD Player: Playing movie - " << movie << std::endl;
    }
    
    void stop() {
        std::cout << "DVD Player: Stopping" << std::endl;
    }
};

// Subsystem: Projector
class Projector {
public:
    void turnOn() {
        std::cout << "Projector: Turning on" << std::endl;
    }
    
    void turnOff() {
        std::cout << "Projector: Turning off" << std::endl;
    }
    
    void setInput(const std::string& input) {
        std::cout << "Projector: Setting input to " << input << std::endl;
    }
    
    void setResolution(const std::string& resolution) {
        std::cout << "Projector: Setting resolution to " << resolution << std::endl;
    }
};

// Subsystem: Sound System
class SoundSystem {
public:
    void turnOn() {
        std::cout << "Sound System: Turning on" << std::endl;
    }
    
    void turnOff() {
        std::cout << "Sound System: Turning off" << std::endl;
    }
    
    void setVolume(int level) {
        std::cout << "Sound System: Setting volume to " << level << std::endl;
    }
    
    void setMode(const std::string& mode) {
        std::cout << "Sound System: Setting mode to " << mode << std::endl;
    }
};

// Subsystem: Lights Controller
class LightsController {
public:
    void dimLights(int percentage) {
        std::cout << "Lights: Dimming to " << percentage << "%" << std::endl;
    }
    
    void turnOnLights() {
        std::cout << "Lights: Turning on" << std::endl;
    }
};

// Subsystem: Screen Controller
class ScreenController {
public:
    void lowerScreen() {
        std::cout << "Screen: Lowering" << std::endl;
    }
    
    void raiseScreen() {
        std::cout << "Screen: Raising" << std::endl;
    }
};
```

### 2. Facade Class

The simplified interface that coordinates the subsystems:

```cpp
// Facade: Home Theater Facade
class HomeTheaterFacade {
public:
    HomeTheaterFacade() {
        dvdPlayer = std::make_unique<DVDPlayer>();
        projector = std::make_unique<Projector>();
        soundSystem = std::make_unique<SoundSystem>();
        lightsController = std::make_unique<LightsController>();
        screenController = std::make_unique<ScreenController>();
    }
    
    // Simplified interface for watching movies
    void watchMovie(const std::string& movie) {
        std::cout << "\n=== Starting Movie: " << movie << " ===" << std::endl;
        
        lightsController->dimLights(30);
        screenController->lowerScreen();
        projector->turnOn();
        projector->setInput("DVD");
        projector->setResolution("1080p");
        soundSystem->turnOn();
        soundSystem->setVolume(70);
        soundSystem->setMode("surround");
        dvdPlayer->turnOn();
        dvdPlayer->playMovie(movie);
        
        std::cout << "=== Movie setup complete ===" << std::endl;
    }
    
    // Simplified interface for ending movie
    void endMovie() {
        std::cout << "\n=== Ending Movie ===" << std::endl;
        
        dvdPlayer->stop();
        dvdPlayer->turnOff();
        soundSystem->turnOff();
        projector->turnOff();
        screenController->raiseScreen();
        lightsController->turnOnLights();
        
        std::cout << "=== Movie ended ===" << std::endl;
    }
    
    // Additional simplified interfaces
    void listenToMusic() {
        std::cout << "\n=== Starting Music ===" << std::endl;
        
        soundSystem->turnOn();
        soundSystem->setVolume(60);
        soundSystem->setMode("stereo");
        lightsController->dimLights(70);
        
        std::cout << "=== Music setup complete ===" << std::endl;
    }
    
private:
    std::unique_ptr<DVDPlayer> dvdPlayer;
    std::unique_ptr<Projector> projector;
    std::unique_ptr<SoundSystem> soundSystem;
    std::unique_ptr<LightsController> lightsController;
    std::unique_ptr<ScreenController> screenController;
};
```

### 3. Client Code

Simple usage of the facade:

```cpp
// Client code using the facade
void demonstrateHomeTheater() {
    std::cout << "=== Home Theater Facade Demo ===" << std::endl;
    
    HomeTheaterFacade homeTheater;
    
    // Simple one-line calls to complex operations
    homeTheater.watchMovie("Avatar");
    
    // Simulate watching movie...
    std::cout << "\n... Enjoying the movie ...\n" << std::endl;
    
    homeTheater.endMovie();
    
    std::cout << "\n--- Switching to music mode ---" << std::endl;
    homeTheater.listenToMusic();
}

int main() {
    demonstrateHomeTheater();
    return 0;
}
```

## Complete Hotel Restaurant Example

### Problem: Complex Restaurant System

Let's implement the hotel restaurant example mentioned in the problem:

![](https://media.geeksforgeeks.org/wp-content/uploads/20240118172434/Problem-Statement-of-Facade-Method-Design-Pattern.jpg)

```cpp
#include <iostream>
#include <string>
#include <memory>

// Subsystem: Menu classes
class Menu {
public:
    virtual ~Menu() = default;
    virtual void display() const = 0;
};

class VegMenu : public Menu {
public:
    void display() const override {
        std::cout << "Vegetarian Menu:" << std::endl;
        std::cout << "- Garden Salad" << std::endl;
        std::cout << "- Vegetable Curry" << std::endl;
        std::cout << "- Pasta Primavera" << std::endl;
    }
};

class NonVegMenu : public Menu {
public:
    void display() const override {
        std::cout << "Non-Vegetarian Menu:" << std::endl;
        std::cout << "- Grilled Chicken" << std::endl;
        std::cout << "- Beef Steak" << std::endl;
        std::cout << "- Fish & Chips" << std::endl;
    }
};

class BothMenu : public Menu {
public:
    void display() const override {
        std::cout << "Mixed Menu (Veg & Non-Veg):" << std::endl;
        std::cout << "- Caesar Salad" << std::endl;
        std::cout << "- Chicken Tikka" << std::endl;
        std::cout << "- Veggie Burger" << std::endl;
        std::cout << "- Lamb Chops" << std::endl;
    }
};

// Subsystem: Restaurant classes
class Restaurant {
public:
    virtual ~Restaurant() = default;
    virtual std::unique_ptr<Menu> getMenu() = 0;
};

class VegRestaurant : public Restaurant {
public:
    std::unique_ptr<Menu> getMenu() override {
        return std::make_unique<VegMenu>();
    }
};

class NonVegRestaurant : public Restaurant {
public:
    std::unique_ptr<Menu> getMenu() override {
        return std::make_unique<NonVegMenu>();
    }
};

class VegNonBothRestaurant : public Restaurant {
public:
    std::unique_ptr<Menu> getMenu() override {
        return std::make_unique<BothMenu>();
    }
};

// Facade: Hotel Keeper
class HotelKeeper {
public:
    HotelKeeper() {
        vegRestaurant = std::make_unique<VegRestaurant>();
        nonVegRestaurant = std::make_unique<NonVegRestaurant>();
        bothRestaurant = std::make_unique<VegNonBothRestaurant>();
    }
    
    // Simplified interface for clients
    void displayVegMenu() {
        std::cout << "\n--- Vegetarian Menu ---" << std::endl;
        auto menu = vegRestaurant->getMenu();
        menu->display();
    }
    
    void displayNonVegMenu() {
        std::cout << "\n--- Non-Vegetarian Menu ---" << std::endl;
        auto menu = nonVegRestaurant->getMenu();
        menu->display();
    }
    
    void displayBothMenu() {
        std::cout << "\n--- Mixed Menu ---" << std::endl;
        auto menu = bothRestaurant->getMenu();
        menu->display();
    }
    
    // Additional convenience method
    void displayAllMenus() {
        std::cout << "=== ALL AVAILABLE MENUS ===" << std::endl;
        displayVegMenu();
        displayNonVegMenu();
        displayBothMenu();
    }
    
private:
    std::unique_ptr<VegRestaurant> vegRestaurant;
    std::unique_ptr<NonVegRestaurant> nonVegRestaurant;
    std::unique_ptr<VegNonBothRestaurant> bothRestaurant;
};

// Client code
void demonstrateHotelRestaurant() {
    std::cout << "=== Hotel Restaurant Facade Demo ===" << std::endl;
    
    HotelKeeper hotelKeeper;
    
    // Client doesn't need to know about different restaurants
    // Just ask the hotel keeper for menus
    
    std::cout << "\nCustomer: Can I see the vegetarian menu?" << std::endl;
    hotelKeeper.displayVegMenu();
    
    std::cout << "\nCustomer: Now show me the non-vegetarian menu." << std::endl;
    hotelKeeper.displayNonVegMenu();
    
    std::cout << "\nCustomer: Actually, show me all menus available." << std::endl;
    hotelKeeper.displayAllMenus();
}
```

## Advanced Example: Computer System Boot

### Complex Computer Boot Process

```cpp
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>

// Subsystem: CPU
class CPU {
public:
    void powerOn() {
        std::cout << "CPU: Powering on..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "CPU: Initialized successfully" << std::endl;
    }
    
    void runPOST() {
        std::cout << "CPU: Running Power-On Self-Test..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "CPU: POST completed successfully" << std::endl;
    }
    
    void initializeCores() {
        std::cout << "CPU: Initializing processor cores..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::cout << "CPU: All cores ready" << std::endl;
    }
};

// Subsystem: Memory
class Memory {
public:
    void initialize() {
        std::cout << "Memory: Initializing RAM..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::cout << "Memory: RAM initialized (16GB ready)" << std::endl;
    }
    
    void runMemoryTest() {
        std::cout << "Memory: Running memory test..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        std::cout << "Memory: Memory test passed" << std::endl;
    }
};

// Subsystem: Storage
class Storage {
public:
    void initialize() {
        std::cout << "Storage: Initializing SSD..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        std::cout << "Storage: SSD ready (1TB available)" << std::endl;
    }
    
    void loadBootloader() {
        std::cout << "Storage: Loading bootloader..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Storage: Bootloader loaded" << std::endl;
    }
};

// Subsystem: Graphics
class Graphics {
public:
    void initialize() {
        std::cout << "Graphics: Initializing GPU..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        std::cout << "Graphics: GPU initialized (NVIDIA RTX 4080)" << std::endl;
    }
    
    void setDisplayMode() {
        std::cout << "Graphics: Setting display mode to 1920x1080..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Graphics: Display ready" << std::endl;
    }
};

// Subsystem: Operating System
class OperatingSystem {
public:
    void loadKernel() {
        std::cout << "OS: Loading kernel..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "OS: Kernel loaded successfully" << std::endl;
    }
    
    void initializeServices() {
        std::cout << "OS: Starting system services..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        std::cout << "OS: Services started (Network, Audio, Input)" << std::endl;
    }
    
    void loadUserInterface() {
        std::cout << "OS: Loading desktop environment..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::cout << "OS: Desktop ready - Welcome!" << std::endl;
    }
};

// Facade: Computer System
class ComputerSystem {
public:
    ComputerSystem() {
        cpu = std::make_unique<CPU>();
        memory = std::make_unique<Memory>();
        storage = std::make_unique<Storage>();
        graphics = std::make_unique<Graphics>();
        os = std::make_unique<OperatingSystem>();
    }
    
    // Simple one-method boot process
    void bootComputer() {
        std::cout << "=== COMPUTER BOOT SEQUENCE ===" << std::endl;
        
        // Hardware initialization
        cpu->powerOn();
        cpu->runPOST();
        memory->initialize();
        memory->runMemoryTest();
        storage->initialize();
        graphics->initialize();
        cpu->initializeCores();
        
        // Boot process
        storage->loadBootloader();
        graphics->setDisplayMode();
        os->loadKernel();
        os->initializeServices();
        os->loadUserInterface();
        
        std::cout << "=== SYSTEM READY ===" << std::endl;
    }
    
    // Additional simplified methods
    void shutdownComputer() {
        std::cout << "\n=== SYSTEM SHUTDOWN ===" << std::endl;
        std::cout << "OS: Saving work and closing applications..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "OS: Stopping services..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Hardware: Powering down..." << std::endl;
        std::cout << "=== SYSTEM OFF ===" << std::endl;
    }
    
    void restartComputer() {
        shutdownComputer();
        std::cout << "\n=== SYSTEM RESTART ===" << std::endl;
        bootComputer();
    }
    
private:
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<Storage> storage;
    std::unique_ptr<Graphics> graphics;
    std::unique_ptr<OperatingSystem> os;
};

// Client code
void demonstrateComputerBoot() {
    std::cout << "=== Computer Boot Facade Demo ===" << std::endl;
    
    ComputerSystem computer;
    
    // Simple interface for complex boot process
    computer.bootComputer();
    
    std::cout << "\n... Using computer for work ...\n" << std::endl;
    
    computer.restartComputer();
}
```

## Banking System Example

### Complex Financial Operations

```cpp
#include <iostream>
#include <string>
#include <memory>

// Subsystem: Account Management
class AccountManager {
public:
    bool verifyAccount(const std::string& accountNumber) {
        std::cout << "Account Manager: Verifying account " << accountNumber << std::endl;
        return true; // Simplified
    }
    
    double getBalance(const std::string& accountNumber) {
        std::cout << "Account Manager: Getting balance for " << accountNumber << std::endl;
        return 1500.0; // Simplified
    }
    
    void updateBalance(const std::string& accountNumber, double newBalance) {
        std::cout << "Account Manager: Updating balance for " << accountNumber 
                  << " to $" << newBalance << std::endl;
    }
};

// Subsystem: Transaction Processor
class TransactionProcessor {
public:
    bool processTransfer(const std::string& from, const std::string& to, double amount) {
        std::cout << "Transaction Processor: Transferring $" << amount 
                  << " from " << from << " to " << to << std::endl;
        return true;
    }
    
    void logTransaction(const std::string& type, double amount) {
        std::cout << "Transaction Processor: Logging " << type 
                  << " transaction of $" << amount << std::endl;
    }
};

// Subsystem: Security System
class SecuritySystem {
public:
    bool authenticateUser(const std::string& userId, const std::string& pin) {
        std::cout << "Security: Authenticating user " << userId << std::endl;
        return (pin == "1234"); // Simplified
    }
    
    bool authorizeTransaction(const std::string& userId, double amount) {
        std::cout << "Security: Authorizing transaction of $" << amount 
                  << " for user " << userId << std::endl;
        return (amount <= 10000.0); // Simplified limit
    }
    
    void generateReceipt(const std::string& transactionId) {
        std::cout << "Security: Generating receipt for transaction " << transactionId << std::endl;
    }
};

// Subsystem: Notification Service
class NotificationService {
public:
    void sendSMS(const std::string& phone, const std::string& message) {
        std::cout << "Notification: Sending SMS to " << phone << ": " << message << std::endl;
    }
    
    void sendEmail(const std::string& email, const std::string& message) {
        std::cout << "Notification: Sending email to " << email << ": " << message << std::endl;
    }
};

// Facade: Banking System
class BankingFacade {
public:
    BankingFacade() {
        accountManager = std::make_unique<AccountManager>();
        transactionProcessor = std::make_unique<TransactionProcessor>();
        securitySystem = std::make_unique<SecuritySystem>();
        notificationService = std::make_unique<NotificationService>();
    }
    
    // Simplified fund transfer
    bool transferFunds(const std::string& userId, const std::string& pin,
                      const std::string& fromAccount, const std::string& toAccount,
                      double amount, const std::string& userPhone) {
        std::cout << "\n=== INITIATING FUND TRANSFER ===" << std::endl;
        
        // Security checks
        if (!securitySystem->authenticateUser(userId, pin)) {
            std::cout << "ERROR: Authentication failed" << std::endl;
            return false;
        }
        
        if (!securitySystem->authorizeTransaction(userId, amount)) {
            std::cout << "ERROR: Transaction not authorized" << std::endl;
            return false;
        }
        
        // Account verification
        if (!accountManager->verifyAccount(fromAccount) || 
            !accountManager->verifyAccount(toAccount)) {
            std::cout << "ERROR: Invalid account" << std::endl;
            return false;
        }
        
        double currentBalance = accountManager->getBalance(fromAccount);
        if (currentBalance < amount) {
            std::cout << "ERROR: Insufficient funds" << std::endl;
            return false;
        }
        
        // Process transaction
        if (!transactionProcessor->processTransfer(fromAccount, toAccount, amount)) {
            std::cout << "ERROR: Transfer failed" << std::endl;
            return false;
        }
        
        // Update accounts
        accountManager->updateBalance(fromAccount, currentBalance - amount);
        accountManager->updateBalance(toAccount, accountManager->getBalance(toAccount) + amount);
        
        // Log and notify
        transactionProcessor->logTransaction("TRANSFER", amount);
        securitySystem->generateReceipt("TXN12345");
        notificationService->sendSMS(userPhone, 
            "Transfer of $" + std::to_string(amount) + " completed successfully");
        
        std::cout << "=== TRANSFER COMPLETED SUCCESSFULLY ===" << std::endl;
        return true;
    }
    
    // Simplified balance check
    double checkBalance(const std::string& userId, const std::string& pin, 
                       const std::string& accountNumber) {
        std::cout << "\n=== CHECKING BALANCE ===" << std::endl;
        
        if (!securitySystem->authenticateUser(userId, pin)) {
            std::cout << "ERROR: Authentication failed" << std::endl;
            return -1.0;
        }
        
        if (!accountManager->verifyAccount(accountNumber)) {
            std::cout << "ERROR: Invalid account" << std::endl;
            return -1.0;
        }
        
        double balance = accountManager->getBalance(accountNumber);
        std::cout << "Current balance: $" << balance << std::endl;
        
        return balance;
    }
    
private:
    std::unique_ptr<AccountManager> accountManager;
    std::unique_ptr<TransactionProcessor> transactionProcessor;
    std::unique_ptr<SecuritySystem> securitySystem;
    std::unique_ptr<NotificationService> notificationService;
};

// Client code
void demonstrateBankingSystem() {
    std::cout << "=== Banking System Facade Demo ===" << std::endl;
    
    BankingFacade banking;
    
    // Simple interface for complex banking operations
    banking.checkBalance("user123", "1234", "ACC001");
    
    std::cout << "\n--- Performing transfer ---" << std::endl;
    banking.transferFunds("user123", "1234", "ACC001", "ACC002", 
                         500.0, "+1234567890");
}
```

## Main Function with All Examples

```cpp
int main() {
    std::cout << "FACADE DESIGN PATTERN DEMONSTRATIONS" << std::endl;
    std::cout << "===================================" << std::endl;
    
    demonstrateHomeTheater();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateHotelRestaurant();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateComputerBoot();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateBankingSystem();
    
    std::cout << "\n=== All demonstrations completed ===" << std::endl;
    return 0;
}
```

## Key Benefits and When to Use

### Benefits

1. **Simplified Interface**: Hides subsystem complexity from clients
2. **Reduced Coupling**: Clients depend only on facade, not subsystems
3. **Easier Maintenance**: Changes in subsystems don't affect clients
4. **Better Organization**: Logical grouping of related functionality
5. **Security**: Can control access to sensitive operations

### When to Use Facade Pattern

1. **Complex Subsystems**: When you have complex subsystems with many interdependencies
2. **Layer Separation**: When you want to separate layers of a system
3. **Legacy Systems**: When wrapping legacy code with a modern interface
4. **Simplified API**: When you want to provide a simple API for a complex system
5. **Entry Points**: When you need a clear entry point to a subsystem

### When NOT to Use

1. **Simple Systems**: When the subsystem is already simple
2. **Need Full Access**: When clients need direct access to all subsystem features
3. **Performance Critical**: When the extra layer causes unacceptable overhead
4. **Over-engineering**: When the pattern adds unnecessary complexity

## Important Considerations

### Facade vs Adapter Pattern

- **Facade**: Simplifies an interface, doesn't change it
- **Adapter**: Changes an interface to make it compatible

### Facade vs Mediator Pattern

- **Facade**: One-way communication (client → facade → subsystems)
- **Mediator**: Multi-way communication between colleagues

### Performance Considerations

- Facade adds an extra layer of indirection
- In performance-critical systems, this might be unacceptable
- Consider direct access for performance-sensitive operations

### Testing Benefits

```cpp
// Facades make testing easier
class TestableHomeTheaterFacade : public HomeTheaterFacade {
    // Can mock subsystems for testing
};
```

## Summary

The Facade Design Pattern provides a simplified interface to a complex subsystem, making it easier to use while hiding internal complexities.

### Key Takeaways:

1. **Wrapper**: Facade wraps complex subsystems with a simple interface
2. **Coordinator**: Coordinates interactions between multiple subsystems
3. **Simplifier**: Reduces learning curve for using complex systems
4. **Maintainability**: Makes systems easier to maintain and evolve
5. **Decoupling**: Reduces dependencies between clients and subsystems

The pattern is particularly valuable when you have complex systems with many interacting components, and you want to provide a clean, simple API for common use cases while still allowing advanced users to access the underlying subsystems directly when needed.