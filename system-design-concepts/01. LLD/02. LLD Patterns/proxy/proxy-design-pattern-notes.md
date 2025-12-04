# Proxy Design Pattern - Complete Guide

## The Problem: Controlled Access to Objects

### The Performance and Security Challenges

![](https://media.geeksforgeeks.org/wp-content/uploads/20250908143158456490/proxy-patterb.webp)

Consider scenarios where direct access to objects causes problems:

**Image Loading Problem:**
- Loading large images from disk is slow
- Loading all images at startup consumes memory unnecessarily
- Need to load images only when actually displayed

**Security Problem:**
- Some operations should be restricted based on user permissions
- Don't want to modify the original object's code
- Need centralized access control

**Remote Access Problem:**
- Objects exist on different machines
- Network communication is complex and error-prone
- Client shouldn't handle network details

### Real-World Analogies

1. **Bank Check**: Proxy for your bank account - controls access to real money
2. **Security Badge**: Proxy for building access - controls who can enter
3. **Assistant**: Proxy for busy executive - filters and prioritizes requests

## The Solution: Proxy Design Pattern

![](https://media.geeksforgeeks.org/wp-content/uploads/20240205165856/proxypatternclassdiagram.webp)

![](https://media.geeksforgeeks.org/wp-content/uploads/20240202170221/changing-of-proxies.webp)


### Core Concept

A proxy acts as a surrogate or placeholder for another object to control access to it. The proxy implements the same interface as the real object, allowing it to be used interchangeably.

### Key Idea: Interception
The proxy sits between client and real object, intercepting requests and adding additional behavior.

## Types of Proxy Patterns

### 1. Virtual Proxy - Lazy Loading

**Problem**: Expensive object creation that should be delayed until needed

### 2. Protection Proxy - Access Control

**Problem**: Need to restrict access to certain operations based on permissions

### 3. Remote Proxy - Network Communication

**Problem**: Objects located on different machines requiring transparent access

### 4. Caching Proxy - Performance Optimization

**Problem**: Repeated expensive operations that can be cached

## Step-by-Step Implementation

### Basic Structure

```
Subject (Interface)
    ↑
    |
    +---- RealSubject (Actual implementation)
    |
    +---- Proxy (Controls access to RealSubject)
```

### 1. Subject Interface

The common interface that both real object and proxy implement:

```cpp
#include <iostream>
#include <string>
#include <memory>

// Subject: Common interface for RealImage and ProxyImage
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
    virtual std::string getFilename() const = 0;
};
```

### 2. RealSubject Class

The actual object that does the real work:

```cpp
// RealSubject: The actual image class that does expensive loading
class RealImage : public Image {
public:
    RealImage(const std::string& filename) : filename(filename) {
        loadImageFromDisk();  // Expensive operation
    }
    
    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
    
    std::string getFilename() const override {
        return filename;
    }
    
private:
    void loadImageFromDisk() {
        std::cout << "Loading " << filename << " from disk... (Expensive operation)" << std::endl;
        // Simulate expensive loading
        std::cout << "Completed loading: " << filename << std::endl;
    }
    
    std::string filename;
};
```

### 3. Proxy Class

Controls access to the real object:

```cpp
// Proxy: Controls access to RealImage, implements lazy loading
class ProxyImage : public Image {
public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}
    
    ~ProxyImage() {
        delete realImage;  // Clean up real image
    }
    
    void display() override {
        // Lazy initialization: Create RealImage only when needed
        if (realImage == nullptr) {
            std::cout << "Proxy: Creating RealImage for " << filename << std::endl;
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
    
    std::string getFilename() const override {
        return filename;
    }
    
private:
    std::string filename;
    RealImage* realImage;  // Reference to real subject
};
```

## Complete Virtual Proxy Example

### Image Loading with Lazy Initialization

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Subject
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
    virtual std::string getName() const = 0;
};

// RealSubject
class HighResolutionImage : public Image {
public:
    HighResolutionImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }
    
    void display() override {
        std::cout << "Displaying high-resolution image: " << filename << std::endl;
    }
    
    std::string getName() const override {
        return filename;
    }
    
private:
    void loadFromDisk() {
        std::cout << "Loading high-resolution image from disk: " << filename << std::endl;
        // Simulate expensive operation
        for (int i = 0; i < 3; ++i) {
            std::cout << "Loading... " << (i + 1) << "/3" << std::endl;
        }
        std::cout << "Finished loading: " << filename << std::endl;
    }
    
    std::string filename;
};

// Proxy with lazy loading
class ImageProxy : public Image {
public:
    ImageProxy(const std::string& filename) : filename(filename), realImage(nullptr) {}
    
    ~ImageProxy() {
        delete realImage;
    }
    
    void display() override {
        if (realImage == nullptr) {
            std::cout << "Proxy: Lazy loading image..." << std::endl;
            realImage = new HighResolutionImage(filename);
        }
        realImage->display();
    }
    
    std::string getName() const override {
        return filename;
    }
    
    // Additional proxy method to check if image is loaded
    bool isLoaded() const {
        return realImage != nullptr;
    }
    
private:
    std::string filename;
    HighResolutionImage* realImage;
};

// Client code demonstrating virtual proxy
void demonstrateVirtualProxy() {
    std::cout << "=== Virtual Proxy Demo: Lazy Image Loading ===" << std::endl;
    
    // Create proxies (no heavy loading yet)
    ImageProxy image1("vacation_photo.jpg");
    ImageProxy image2("family_portrait.png");
    ImageProxy image3("landscape.tiff");
    
    std::cout << "\nProxies created, but no images loaded yet." << std::endl;
    std::cout << "Image1 loaded: " << (image1.isLoaded() ? "Yes" : "No") << std::endl;
    std::cout << "Image2 loaded: " << (image2.isLoaded() ? "Yes" : "No") << std::endl;
    std::cout << "Image3 loaded: " << (image3.isLoaded() ? "Yes" : "No") << std::endl;
    
    std::cout << "\n--- Displaying image1 (will load now) ---" << std::endl;
    image1.display();
    
    std::cout << "\n--- Displaying image1 again (already loaded) ---" << std::endl;
    image1.display();
    
    std::cout << "\n--- Displaying image2 (will load now) ---" << std::endl;
    image2.display();
    
    std::cout << "\nFinal status:" << std::endl;
    std::cout << "Image1 loaded: " << (image1.isLoaded() ? "Yes" : "No") << std::endl;
    std::cout << "Image2 loaded: " << (image2.isLoaded() ? "Yes" : "No") << std::endl;
    std::cout << "Image3 loaded: " << (image3.isLoaded() ? "Yes" : "No") << std::endl;
}
```

## Protection Proxy Example

### Access Control with Proxy

```cpp
#include <iostream>
#include <string>
#include <vector>

// Subject
class Database {
public:
    virtual ~Database() = default;
    virtual void query(const std::string& sql) = 0;
    virtual void update(const std::string& sql) = 0;
    virtual void deleteRecord(const std::string& sql) = 0;
};

// RealSubject
class RealDatabase : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << std::endl;
    }
    
    void update(const std::string& sql) override {
        std::cout << "Executing update: " << sql << std::endl;
    }
    
    void deleteRecord(const std::string& sql) override {
        std::cout << "Executing delete: " << sql << std::endl;
    }
};

// User roles
enum class UserRole {
    GUEST,
    USER, 
    ADMIN
};

// Protection Proxy
class SecureDatabaseProxy : public Database {
public:
    SecureDatabaseProxy(UserRole role) : userRole(role), realDatabase(new RealDatabase()) {}
    
    ~SecureDatabaseProxy() {
        delete realDatabase;
    }
    
    void query(const std::string& sql) override {
        // Everyone can query
        std::cout << "Proxy: Allowing query for role " << roleToString(userRole) << std::endl;
        realDatabase->query(sql);
    }
    
    void update(const std::string& sql) override {
        // Only users and admins can update
        if (userRole == UserRole::GUEST) {
            std::cout << "Proxy: BLOCKED - Update not allowed for role " << roleToString(userRole) << std::endl;
            return;
        }
        std::cout << "Proxy: Allowing update for role " << roleToString(userRole) << std::endl;
        realDatabase->update(sql);
    }
    
    void deleteRecord(const std::string& sql) override {
        // Only admins can delete
        if (userRole != UserRole::ADMIN) {
            std::cout << "Proxy: BLOCKED - Delete not allowed for role " << roleToString(userRole) << std::endl;
            return;
        }
        std::cout << "Proxy: Allowing delete for role " << roleToString(userRole) << std::endl;
        realDatabase->deleteRecord(sql);
    }
    
private:
    std::string roleToString(UserRole role) {
        switch (role) {
            case UserRole::GUEST: return "GUEST";
            case UserRole::USER: return "USER";
            case UserRole::ADMIN: return "ADMIN";
            default: return "UNKNOWN";
        }
    }
    
    UserRole userRole;
    RealDatabase* realDatabase;
};

// Client code for protection proxy
void demonstrateProtectionProxy() {
    std::cout << "\n=== Protection Proxy Demo: Database Access Control ===" << std::endl;
    
    // Different users with different roles
    SecureDatabaseProxy guestDb(UserRole::GUEST);
    SecureDatabaseProxy userDb(UserRole::USER);
    SecureDatabaseProxy adminDb(UserRole::ADMIN);
    
    std::cout << "\n--- Guest User Access ---" << std::endl;
    guestDb.query("SELECT * FROM products");
    guestDb.update("UPDATE products SET price=100");
    guestDb.deleteRecord("DELETE FROM products");
    
    std::cout << "\n--- Regular User Access ---" << std::endl;
    userDb.query("SELECT * FROM products");
    userDb.update("UPDATE products SET price=100");
    userDb.deleteRecord("DELETE FROM products");
    
    std::cout << "\n--- Admin User Access ---" << std::endl;
    adminDb.query("SELECT * FROM products");
    adminDb.update("UPDATE products SET price=100");
    adminDb.deleteRecord("DELETE FROM products");
}
```

## Caching Proxy Example

### Expensive Operation Caching

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

// Subject
class Calculator {
public:
    virtual ~Calculator() = default;
    virtual double compute(double value) = 0;
};

// RealSubject - Expensive computation
class ExpensiveCalculator : public Calculator {
public:
    double compute(double value) override {
        std::cout << "ExpensiveCalculator: Computing for " << value << " (this is slow)..." << std::endl;
        
        // Simulate expensive computation
        double result = 0;
        for (int i = 0; i < 1000000; ++i) {
            result += std::sqrt(value + i) * std::sin(value);
        }
        
        std::cout << "ExpensiveCalculator: Result = " << result << std::endl;
        return result;
    }
};

// Caching Proxy
class CachingCalculatorProxy : public Calculator {
public:
    CachingCalculatorProxy() : realCalculator(new ExpensiveCalculator()) {}
    
    ~CachingCalculatorProxy() {
        delete realCalculator;
    }
    
    double compute(double value) override {
        // Check cache first
        auto it = cache.find(value);
        if (it != cache.end()) {
            std::cout << "CachingProxy: Cache HIT for " << value << " -> " << it->second << std::endl;
            return it->second;
        }
        
        // Cache miss - compute and cache
        std::cout << "CachingProxy: Cache MISS for " << value << std::endl;
        double result = realCalculator->compute(value);
        cache[value] = result;
        
        std::cout << "CachingProxy: Cached result for " << value << std::endl;
        return result;
    }
    
    void clearCache() {
        std::cout << "CachingProxy: Cache cleared (" << cache.size() << " entries removed)" << std::endl;
        cache.clear();
    }
    
    size_t getCacheSize() const {
        return cache.size();
    }
    
private:
    ExpensiveCalculator* realCalculator;
    std::unordered_map<double, double> cache;
};

// Client code for caching proxy
void demonstrateCachingProxy() {
    std::cout << "\n=== Caching Proxy Demo: Expensive Computation ===" << std::endl;
    
    CachingCalculatorProxy calculator;
    
    std::cout << "\n--- First computation (will be slow) ---" << std::endl;
    calculator.compute(10.0);
    
    std::cout << "\n--- Same computation again (will be fast from cache) ---" << std::endl;
    calculator.compute(10.0);
    
    std::cout << "\n--- Different computation (will be slow) ---" << std::endl;
    calculator.compute(20.0);
    
    std::cout << "\n--- Repeat previous computations (all fast from cache) ---" << std::endl;
    calculator.compute(10.0);
    calculator.compute(20.0);
    
    std::cout << "\nCache size: " << calculator.getCacheSize() << " entries" << std::endl;
    
    std::cout << "\n--- Clear cache and compute again ---" << std::endl;
    calculator.clearCache();
    calculator.compute(10.0);
}
```

## Remote Proxy Example

### Simplified Remote Service Access

```cpp
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Subject - Represents a remote service
class PaymentService {
public:
    virtual ~PaymentService() = default;
    virtual bool processPayment(const std::string& orderId, double amount) = 0;
    virtual std::string getPaymentStatus(const std::string& orderId) = 0;
};

// RealSubject - Simulates remote payment service
class RemotePaymentService : public PaymentService {
public:
    bool processPayment(const std::string& orderId, double amount) override {
        std::cout << "RemotePaymentService: Processing payment for order " << orderId 
                  << " amount $" << amount << std::endl;
        
        // Simulate network delay
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Simulate processing
        bool success = (std::stoi(orderId) % 2 == 0); // Even orders succeed
        std::cout << "RemotePaymentService: Payment " << (success ? "SUCCESS" : "FAILED") << std::endl;
        
        return success;
    }
    
    std::string getPaymentStatus(const std::string& orderId) override {
        std::cout << "RemotePaymentService: Getting status for order " << orderId << std::endl;
        
        // Simulate network delay
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        return "COMPLETED";
    }
};

// Remote Proxy - Handles network communication transparently
class PaymentServiceProxy : public PaymentService {
public:
    PaymentServiceProxy() : remoteService(new RemotePaymentService()) {}
    
    ~PaymentServiceProxy() {
        delete remoteService;
    }
    
    bool processPayment(const std::string& orderId, double amount) override {
        std::cout << "PaymentProxy: Preparing to process payment..." << std::endl;
        
        // Proxy handles all network-related concerns
        std::cout << "PaymentProxy: Establishing secure connection..." << std::endl;
        std::cout << "PaymentProxy: Serializing request data..." << std::endl;
        
        // Delegate to real remote service
        bool result = remoteService->processPayment(orderId, amount);
        
        std::cout << "PaymentProxy: Processing response..." << std::endl;
        std::cout << "PaymentProxy: Closing connection..." << std::endl;
        
        return result;
    }
    
    std::string getPaymentStatus(const std::string& orderId) override {
        std::cout << "PaymentProxy: Getting payment status..." << std::endl;
        
        // Proxy handles network communication
        std::cout << "PaymentProxy: Sending status request..." << std::endl;
        
        std::string status = remoteService->getPaymentStatus(orderId);
        
        std::cout << "PaymentProxy: Received status: " << status << std::endl;
        return status;
    }
    
private:
    RemotePaymentService* remoteService;
};

// Client code for remote proxy
void demonstrateRemoteProxy() {
    std::cout << "\n=== Remote Proxy Demo: Payment Service ===" << std::endl;
    
    PaymentServiceProxy paymentService;
    
    std::cout << "\n--- Processing payment through proxy ---" << std::endl;
    bool result1 = paymentService.processPayment("1001", 250.0);
    std::cout << "Client: Payment result: " << (result1 ? "SUCCESS" : "FAILED") << std::endl;
    
    std::cout << "\n--- Getting payment status through proxy ---" << std::endl;
    std::string status = paymentService.getPaymentStatus("1001");
    std::cout << "Client: Payment status: " << status << std::endl;
    
    std::cout << "\n--- Processing another payment ---" << std::endl;
    bool result2 = paymentService.processPayment("1002", 150.0);
    std::cout << "Client: Payment result: " << (result2 ? "SUCCESS" : "FAILED") << std::endl;
}
```

## Smart Pointer as Proxy Example

### C++ Smart Pointers as Built-in Proxies

```cpp
#include <iostream>
#include <memory>

// Resource-intensive class
class ExpensiveResource {
public:
    ExpensiveResource() {
        std::cout << "ExpensiveResource: Constructor - Allocating heavy resources" << std::endl;
    }
    
    ~ExpensiveResource() {
        std::cout << "ExpensiveResource: Destructor - Releasing heavy resources" << std::endl;
    }
    
    void doWork() {
        std::cout << "ExpensiveResource: Doing important work" << std::endl;
    }
};

// Custom smart pointer as proxy
template<typename T>
class ResourceProxy {
public:
    ResourceProxy() : resource(nullptr) {}
    
    ~ResourceProxy() {
        delete resource;
    }
    
    T* operator->() {
        if (resource == nullptr) {
            std::cout << "ResourceProxy: Lazy loading resource..." << std::endl;
            resource = new T();
        }
        return resource;
    }
    
    T& operator*() {
        if (resource == nullptr) {
            std::cout << "ResourceProxy: Lazy loading resource..." << std::endl;
            resource = new T();
        }
        return *resource;
    }
    
private:
    T* resource;
};

void demonstrateSmartPointerProxy() {
    std::cout << "\n=== Smart Pointer as Proxy Demo ===" << std::endl;
    
    std::cout << "\n--- Creating proxy (no resource allocated yet) ---" << std::endl;
    ResourceProxy<ExpensiveResource> proxy;
    
    std::cout << "\n--- Using resource through proxy (will load now) ---" << std::endl;
    proxy->doWork();
    
    std::cout << "\n--- Using resource again (already loaded) ---" << std::endl;
    proxy->doWork();
    
    std::cout << "\n--- End of scope (proxy destructor cleans up) ---" << std::endl;
}
```

## Main Function Demonstrating All Proxy Types

```cpp
int main() {
    std::cout << "PROXY DESIGN PATTERN DEMONSTRATIONS" << std::endl;
    std::cout << "===================================" << std::endl;
    
    demonstrateVirtualProxy();      // Lazy loading
    demonstrateProtectionProxy();   // Access control  
    demonstrateCachingProxy();      // Performance optimization
    demonstrateRemoteProxy();       // Network transparency
    demonstrateSmartPointerProxy(); // Built-in C++ proxies
    
    std::cout << "\n=== All demonstrations completed ===" << std::endl;
    
    return 0;
}
```

## Key Benefits and When to Use

### Benefits

1. **Lazy Loading**: Defer expensive operations until needed
2. **Access Control**: Add security without modifying real object
3. **Caching**: Improve performance for repeated operations
4. **Remote Access**: Simplify network communication
5. **Separation of Concerns**: Cross-cutting concerns handled in proxy
6. **Open/Closed Principle**: Extend functionality without changing real object

### When to Use Proxy Pattern

1. **Virtual Proxy**: When object creation is expensive and should be delayed
2. **Protection Proxy**: When access control is needed
3. **Remote Proxy**: When objects are in different address spaces
4. **Caching Proxy**: When results of expensive operations can be cached
5. **Logging Proxy**: When you need to log access to objects
6. **Smart Reference**: When you need additional actions when object is accessed

### When NOT to Use

1. **Simple Objects**: When objects are lightweight and creation is cheap
2. **Direct Access**: When no additional functionality is needed
3. **Performance Critical**: When proxy overhead is unacceptable
4. **Over-engineering**: When the problem doesn't justify the complexity

## Important Considerations

### Performance Implications
- Proxies add an extra layer of indirection
- Consider overhead vs benefits
- Use only when additional functionality is valuable

### Memory Management
- Be careful with ownership in C++
- Consider using smart pointers
- Ensure proper cleanup in destructors

### Interface Consistency
- Proxy must implement the same interface as real subject
- Client should not know it's using a proxy
- Maintain behavioral transparency

## Summary

The Proxy Design Pattern provides a surrogate or placeholder for another object to control access to it. Key takeaways:

1. **Interception**: Proxy sits between client and real object, intercepting requests
2. **Transparency**: Client doesn't know it's using a proxy
3. **Flexibility**: Different proxy types solve different problems
4. **Separation**: Cross-cutting concerns handled separately from business logic

The pattern is particularly valuable when you need to add functionality like lazy loading, access control, caching, or remote communication without modifying the original object's code.