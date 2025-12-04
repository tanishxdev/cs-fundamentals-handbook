# Strategy Design Pattern - Complete Guide
![](https://media.geeksforgeeks.org/wp-content/uploads/20250911173103416801/Strategy-design-pattern.webp)
## The Problem: Multiple Algorithms for the Same Task

### The Algorithm Selection Problem

Imagine you're building a navigation app that can calculate routes using different methods:

- Driving directions
- Walking directions  
- Public transportation
- Cycling routes

Without the Strategy pattern, you might end up with:

```cpp
// Problematic approach without Strategy pattern
class Navigation {
public:
    void calculateRoute(const std::string& from, const std::string& to, 
                       const std::string& mode) {
        if (mode == "driving") {
            // Complex driving route calculation
            calculateDrivingRoute(from, to);
        } else if (mode == "walking") {
            // Complex walking route calculation  
            calculateWalkingRoute(from, to);
        } else if (mode == "transit") {
            // Complex transit route calculation
            calculateTransitRoute(from, to);
        } else if (mode == "cycling") {
            // Complex cycling route calculation
            calculateCyclingRoute(from, to);
        }
        // Adding new modes requires modifying this class
    }
    
private:
    void calculateDrivingRoute(const std::string& from, const std::string& to) {
        // Complex implementation
    }
    
    void calculateWalkingRoute(const std::string& from, const std::string& to) {
        // Complex implementation  
    }
    
    // ... and so on
};
```

**Problems with this approach:**
1. **Violates Open/Closed Principle**: Adding new algorithms requires modifying existing code
2. **Tight Coupling**: Navigation class knows about all algorithm implementations
3. **Hard to Test**: Difficult to test individual algorithms in isolation
4. **Code Duplication**: Similar logic might be repeated across methods
5. **Complex Conditional Logic**: Long if-else chains become hard to maintain

### Real-World Scenarios

1. **Payment Processing**: Credit card, PayPal, bank transfer, cryptocurrency
2. **Compression Algorithms**: ZIP, GZIP, RAR, 7z
3. **Image Filters**: Black & white, sepia, blur, sharpen
4. **Sorting Algorithms**: Quick sort, merge sort, bubble sort

## The Solution: Strategy Design Pattern


![](https://media.geeksforgeeks.org/wp-content/uploads/20240207154820/StrategyDesignPatternExample.webp)

### Core Concept

The Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from clients that use it.

**Simple Analogy**: 
- Navigation app with different route options
- Same destination, different ways to get there
- You can switch between driving, walking, transit without changing your destination

## Step-by-Step Implementation

### Basic Structure

```
Context (Uses Strategy)
    ↑
    |
Strategy Interface
    ↑
    |
    +---- Concrete Strategy A
    |
    +---- Concrete Strategy B
    |
    +---- Concrete Strategy C
```

### 1. Strategy Interface

Defines the common interface for all algorithms:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Strategy Interface
class RouteStrategy {
public:
    virtual ~RouteStrategy() = default;
    virtual void calculateRoute(const std::string& from, const std::string& to) = 0;
    virtual std::string getStrategyName() const = 0;
};
```

### 2. Concrete Strategies

Implement different algorithms:

```cpp
// Concrete Strategy: Driving
class DrivingStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating driving route from " << from << " to " << to << std::endl;
        std::cout << " - Considering highways and traffic conditions" << std::endl;
        std::cout << " - Estimating fuel consumption" << std::endl;
        std::cout << " - Route calculated: 15.2 miles, 25 minutes" << std::endl;
    }
    
    std::string getStrategyName() const override {
        return "Driving";
    }
};

// Concrete Strategy: Walking
class WalkingStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating walking route from " << from << " to " << to << std::endl;
        std::cout << " - Avoiding highways and busy roads" << std::endl;
        std::cout << " - Considering pedestrian pathways" << std::endl;
        std::cout << " - Route calculated: 1.2 miles, 20 minutes" << std::endl;
    }
    
    std::string getStrategyName() const override {
        return "Walking";
    }
};

// Concrete Strategy: Public Transit
class TransitStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating public transit route from " << from << " to " << to << std::endl;
        std::cout << " - Finding bus/train schedules" << std::endl;
        std::cout << " - Calculating transfers and wait times" << std::endl;
        std::cout << " - Route calculated: 3 stops, 35 minutes, $2.50" << std::endl;
    }
    
    std::string getStrategyName() const override {
        return "Public Transit";
    }
};

// Concrete Strategy: Cycling
class CyclingStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating cycling route from " << from << " to " << to << std::endl;
        std::cout << " - Finding bike lanes and trails" << std::endl;
        std::cout << " - Considering elevation changes" << std::endl;
        std::cout << " - Route calculated: 3.5 miles, 18 minutes" << std::endl;
    }
    
    std::string getStrategyName() const override {
        return "Cycling";
    }
};
```

### 3. Context Class

Uses the strategy and can switch between them:

```cpp
// Context: Navigation System
class NavigationSystem {
public:
    NavigationSystem(std::unique_ptr<RouteStrategy> strategy = nullptr) 
        : strategy_(std::move(strategy)) {}
    
    // Set strategy at runtime
    void setStrategy(std::unique_ptr<RouteStrategy> strategy) {
        strategy_ = std::move(strategy);
    }
    
    // Execute the current strategy
    void calculateRoute(const std::string& from, const std::string& to) {
        if (!strategy_) {
            std::cout << "Error: No route strategy selected" << std::endl;
            return;
        }
        
        std::cout << "\n=== Using " << strategy_->getStrategyName() << " Strategy ===" << std::endl;
        strategy_->calculateRoute(from, to);
    }
    
    // Get current strategy name
    std::string getCurrentStrategy() const {
        return strategy_ ? strategy_->getStrategyName() : "None";
    }
    
private:
    std::unique_ptr<RouteStrategy> strategy_;
};
```

### 4. Client Code

```cpp
// Client code demonstrating strategy pattern
void demonstrateNavigation() {
    std::cout << "=== Navigation System with Strategy Pattern ===" << std::endl;
    
    NavigationSystem nav;
    
    // Start with driving strategy
    nav.setStrategy(std::make_unique<DrivingStrategy>());
    nav.calculateRoute("Home", "Office");
    
    // Switch to walking strategy
    nav.setStrategy(std::make_unique<WalkingStrategy>());
    nav.calculateRoute("Home", "Grocery Store");
    
    // Switch to transit strategy  
    nav.setStrategy(std::make_unique<TransitStrategy>());
    nav.calculateRoute("Home", "Airport");
    
    // Switch to cycling strategy
    nav.setStrategy(std::make_unique<CyclingStrategy>());
    nav.calculateRoute("Home", "Park");
}
```

## Complete Payment Processing Example

### Problem: Multiple Payment Methods

```cpp
#include <iostream>
#include <string>
#include <memory>

// Strategy Interface
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool processPayment(double amount) = 0;
    virtual std::string getMethodName() const = 0;
};

// Concrete Strategy: Credit Card
class CreditCardStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing credit card payment of $" << amount << std::endl;
        std::cout << " - Validating card details" << std::endl;
        std::cout << " - Charging amount to card" << std::endl;
        std::cout << " - Payment successful!" << std::endl;
        return true;
    }
    
    std::string getMethodName() const override {
        return "Credit Card";
    }
};

// Concrete Strategy: PayPal
class PayPalStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
        std::cout << " - Redirecting to PayPal" << std::endl;
        std::cout << " - Authorizing payment" << std::endl;
        std::cout << " - Payment confirmed!" << std::endl;
        return true;
    }
    
    std::string getMethodName() const override {
        return "PayPal";
    }
};

// Concrete Strategy: Bank Transfer
class BankTransferStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing bank transfer of $" << amount << std::endl;
        std::cout << " - Initiating wire transfer" << std::endl;
        std::cout << " - Waiting for confirmation" << std::endl;
        std::cout << " - Transfer completed!" << std::endl;
        return true;
    }
    
    std::string getMethodName() const override {
        return "Bank Transfer";
    }
};

// Concrete Strategy: Cryptocurrency
class CryptoStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing cryptocurrency payment of $" << amount << std::endl;
        std::cout << " - Converting to Bitcoin equivalent" << std::endl;
        std::cout << " - Creating blockchain transaction" << std::endl;
        std::cout << " - Transaction confirmed on blockchain!" << std::endl;
        return true;
    }
    
    std::string getMethodName() const override {
        return "Cryptocurrency";
    }
};

// Context: Payment Processor
class PaymentProcessor {
public:
    PaymentProcessor(std::unique_ptr<PaymentStrategy> strategy = nullptr)
        : strategy_(std::move(strategy)) {}
    
    void setPaymentMethod(std::unique_ptr<PaymentStrategy> strategy) {
        strategy_ = std::move(strategy);
    }
    
    bool makePayment(double amount) {
        if (!strategy_) {
            std::cout << "Error: No payment method selected" << std::endl;
            return false;
        }
        
        std::cout << "\n=== Processing Payment via " << strategy_->getMethodName() << " ===" << std::endl;
        return strategy_->processPayment(amount);
    }
    
    std::string getCurrentMethod() const {
        return strategy_ ? strategy_->getMethodName() : "None";
    }
    
private:
    std::unique_ptr<PaymentStrategy> strategy_;
};

// Client code for payment processing
void demonstratePaymentProcessing() {
    std::cout << "=== Payment Processing with Strategy Pattern ===" << std::endl;
    
    PaymentProcessor processor;
    
    // Process payments with different methods
    processor.setPaymentMethod(std::make_unique<CreditCardStrategy>());
    processor.makePayment(100.0);
    
    processor.setPaymentMethod(std::make_unique<PayPalStrategy>());
    processor.makePayment(50.0);
    
    processor.setPaymentMethod(std::make_unique<BankTransferStrategy>());
    processor.makePayment(500.0);
    
    processor.setPaymentMethod(std::make_unique<CryptoStrategy>());
    processor.makePayment(75.0);
}
```

## Advanced Example: Image Processing Filters

### Problem: Multiple Image Filters

```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Strategy Interface for Image Filters
class ImageFilter {
public:
    virtual ~ImageFilter() = default;
    virtual void apply(const std::string& image) = 0;
    virtual std::string getName() const = 0;
};

// Concrete Strategy: Grayscale Filter
class GrayscaleFilter : public ImageFilter {
public:
    void apply(const std::string& image) override {
        std::cout << "Applying Grayscale filter to: " << image << std::endl;
        std::cout << " - Converting colors to grayscale" << std::endl;
        std::cout << " - Adjusting brightness and contrast" << std::endl;
        std::cout << " - Grayscale filter applied successfully!" << std::endl;
    }
    
    std::string getName() const override {
        return "Grayscale";
    }
};

// Concrete Strategy: Sepia Filter
class SepiaFilter : public ImageFilter {
public:
    void apply(const std::string& image) override {
        std::cout << "Applying Sepia filter to: " << image << std::endl;
        std::cout << " - Adding brownish tones" << std::endl;
        std::cout << " - Creating vintage effect" << std::endl;
        std::cout << " - Sepia filter applied successfully!" << std::endl;
    }
    
    std::string getName() const override {
        return "Sepia";
    }
};

// Concrete Strategy: Blur Filter
class BlurFilter : public ImageFilter {
public:
    void apply(const std::string& image) override {
        std::cout << "Applying Blur filter to: " << image << std::endl;
        std::cout << " - Calculating convolution matrix" << std::endl;
        std::cout << " - Smoothing image pixels" << std::endl;
        std::cout << " - Blur filter applied successfully!" << std::endl;
    }
    
    std::string getName() const override {
        return "Blur";
    }
};

// Concrete Strategy: Sharpen Filter
class SharpenFilter : public ImageFilter {
public:
    void apply(const std::string& image) override {
        std::cout << "Applying Sharpen filter to: " << image << std::endl;
        std::cout << " - Enhancing edges and details" << std::endl;
        std::cout << " - Increasing contrast along edges" << std::endl;
        std::cout << " - Sharpen filter applied successfully!" << std::endl;
    }
    
    std::string getName() const override {
        return "Sharpen";
    }
};

// Context: Image Processor
class ImageProcessor {
public:
    ImageProcessor(std::unique_ptr<ImageFilter> filter = nullptr)
        : currentFilter_(std::move(filter)) {}
    
    void setFilter(std::unique_ptr<ImageFilter> filter) {
        currentFilter_ = std::move(filter);
    }
    
    void processImage(const std::string& imagePath) {
        if (!currentFilter_) {
            std::cout << "Error: No filter selected" << std::endl;
            return;
        }
        
        std::cout << "\n=== Processing Image with " << currentFilter_->getName() << " Filter ===" << std::endl;
        currentFilter_->apply(imagePath);
    }
    
    // Method to apply multiple filters sequentially
    void applyFilterChain(const std::string& imagePath, 
                         const std::vector<std::unique_ptr<ImageFilter>>& filters) {
        std::cout << "\n=== Applying Filter Chain to: " << imagePath << " ===" << std::endl;
        
        for (const auto& filter : filters) {
            filter->apply(imagePath);
        }
        
        std::cout << "=== Filter chain completed ===" << std::endl;
    }
    
    std::string getCurrentFilter() const {
        return currentFilter_ ? currentFilter_->getName() : "None";
    }
    
private:
    std::unique_ptr<ImageFilter> currentFilter_;
};

// Client code for image processing
void demonstrateImageProcessing() {
    std::cout << "=== Image Processing with Strategy Pattern ===" << std::endl;
    
    ImageProcessor processor;
    
    // Apply different filters to the same image
    std::string image = "vacation_photo.jpg";
    
    processor.setFilter(std::make_unique<GrayscaleFilter>());
    processor.processImage(image);
    
    processor.setFilter(std::make_unique<SepiaFilter>());
    processor.processImage(image);
    
    processor.setFilter(std::make_unique<BlurFilter>());
    processor.processImage(image);
    
    processor.setFilter(std::make_unique<SharpenFilter>());
    processor.processImage(image);
    
    // Demonstrate filter chain
    std::cout << "\n--- Applying Filter Chain ---" << std::endl;
    std::vector<std::unique_ptr<ImageFilter>> filterChain;
    filterChain.push_back(std::make_unique<SharpenFilter>());
    filterChain.push_back(std::make_unique<SepiaFilter>());
    filterChain.push_back(std::make_unique<BlurFilter>());
    
    processor.applyFilterChain("portrait.png", filterChain);
}
```

## Real-World Example: Compression Algorithms

### Problem: Multiple Compression Methods

```cpp
#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Strategy Interface for Compression
class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual void compress(const std::string& file) = 0;
    virtual void decompress(const std::string& file) = 0;
    virtual std::string getName() const = 0;
    virtual double getCompressionRatio() const = 0;
};

// Concrete Strategy: ZIP Compression
class ZipCompression : public CompressionStrategy {
public:
    void compress(const std::string& file) override {
        std::cout << "Compressing " << file << " using ZIP" << std::endl;
        std::cout << " - Using DEFLATE algorithm" << std::endl;
        std::cout << " - Creating archive with multiple files" << std::endl;
        std::cout << " - ZIP compression completed!" << std::endl;
    }
    
    void decompress(const std::string& file) override {
        std::cout << "Decompressing " << file << " from ZIP archive" << std::endl;
        std::cout << " - Extracting files from archive" << std::endl;
        std::cout << " - Restoring original file structure" << std::endl;
        std::cout << " - ZIP decompression completed!" << std::endl;
    }
    
    std::string getName() const override {
        return "ZIP";
    }
    
    double getCompressionRatio() const override {
        return 0.6; // 40% compression
    }
};

// Concrete Strategy: GZIP Compression
class GzipCompression : public CompressionStrategy {
public:
    void compress(const std::string& file) override {
        std::cout << "Compressing " << file << " using GZIP" << std::endl;
        std::cout << " - Using LZ77 and Huffman coding" << std::endl;
        std::cout << " - Optimized for single files" << std::endl;
        std::cout << " - GZIP compression completed!" << std::endl;
    }
    
    void decompress(const std::string& file) override {
        std::cout << "Decompressing " << file << " from GZIP" << std::endl;
        std::cout << " - Inflating compressed data" << std::endl;
        std::cout << " - Restoring original file" << std::endl;
        std::cout << " - GZIP decompression completed!" << std::endl;
    }
    
    std::string getName() const override {
        return "GZIP";
    }
    
    double getCompressionRatio() const override {
        return 0.5; // 50% compression
    }
};

// Concrete Strategy: RAR Compression
class RarCompression : public CompressionStrategy {
public:
    void compress(const std::string& file) override {
        std::cout << "Compressing " << file << " using RAR" << std::endl;
        std::cout << " - Using proprietary compression algorithm" << std::endl;
        std::cout << " - Supporting recovery records" << std::endl;
        std::cout << " - RAR compression completed!" << std::endl;
    }
    
    void decompress(const std::string& file) override {
        std::cout << "Decompressing " << file << " from RAR archive" << std::endl;
        std::cout << " - Extracting with error recovery" << std::endl;
        std::cout << " - Restoring file integrity" << std::endl;
        std::cout << " - RAR decompression completed!" << std::endl;
    }
    
    std::string getName() const override {
        return "RAR";
    }
    
    double getCompressionRatio() const override {
        return 0.4; // 60% compression
    }
};

// Context: File Compressor
class FileCompressor {
public:
    FileCompressor(std::unique_ptr<CompressionStrategy> strategy = nullptr)
        : currentStrategy_(std::move(strategy)) {}
    
    void setCompressionStrategy(std::unique_ptr<CompressionStrategy> strategy) {
        currentStrategy_ = std::move(strategy);
    }
    
    void compressFile(const std::string& file) {
        if (!currentStrategy_) {
            std::cout << "Error: No compression strategy selected" << std::endl;
            return;
        }
        
        std::cout << "\n=== Compressing with " << currentStrategy_->getName() << " ===" << std::endl;
        std::cout << "Compression Ratio: " << (currentStrategy_->getCompressionRatio() * 100) << "%" << std::endl;
        currentStrategy_->compress(file);
    }
    
    void decompressFile(const std::string& file) {
        if (!currentStrategy_) {
            std::cout << "Error: No compression strategy selected" << std::endl;
            return;
        }
        
        std::cout << "\n=== Decompressing with " << currentStrategy_->getName() << " ===" << std::endl;
        currentStrategy_->decompress(file);
    }
    
    void compareStrategies(const std::string& file, 
                          const std::vector<std::unique_ptr<CompressionStrategy>>& strategies) {
        std::cout << "\n=== Comparing Compression Strategies ===" << std::endl;
        std::cout << "File: " << file << std::endl;
        
        for (const auto& strategy : strategies) {
            std::cout << "\nStrategy: " << strategy->getName() << std::endl;
            std::cout << "Compression Ratio: " << (strategy->getCompressionRatio() * 100) << "%" << std::endl;
            strategy->compress(file);
        }
    }
    
private:
    std::unique_ptr<CompressionStrategy> currentStrategy_;
};

// Client code for compression
void demonstrateCompression() {
    std::cout << "=== File Compression with Strategy Pattern ===" << std::endl;
    
    FileCompressor compressor;
    std::string file = "large_document.pdf";
    
    // Test different compression strategies
    compressor.setCompressionStrategy(std::make_unique<ZipCompression>());
    compressor.compressFile(file);
    compressor.decompressFile(file + ".zip");
    
    compressor.setCompressionStrategy(std::make_unique<GzipCompression>());
    compressor.compressFile(file);
    compressor.decompressFile(file + ".gz");
    
    compressor.setCompressionStrategy(std::make_unique<RarCompression>());
    compressor.compressFile(file);
    compressor.decompressFile(file + ".rar");
    
    // Compare all strategies
    std::cout << "\n--- Strategy Comparison ---" << std::endl;
    std::vector<std::unique_ptr<CompressionStrategy>> strategies;
    strategies.push_back(std::make_unique<ZipCompression>());
    strategies.push_back(std::make_unique<GzipCompression>());
    strategies.push_back(std::make_unique<RarCompression>());
    
    compressor.compareStrategies("data_backup.db", strategies);
}
```

## Main Function with All Examples

```cpp
int main() {
    std::cout << "STRATEGY DESIGN PATTERN DEMONSTRATIONS" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    demonstrateNavigation();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstratePaymentProcessing();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateImageProcessing();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateCompression();
    
    std::cout << "\n=== All demonstrations completed ===" << std::endl;
    return 0;
}
```

## Key Benefits and When to Use

### Benefits

1. **Open/Closed Principle**: New strategies can be added without modifying existing code
2. **Eliminates Conditional Logic**: No complex if-else or switch statements
3. **Runtime Flexibility**: Algorithms can be swapped at runtime
4. **Separation of Concerns**: Each algorithm is encapsulated in its own class
5. **Testability**: Easy to test individual strategies in isolation
6. **Code Reuse**: Strategies can be reused across different contexts

### When to Use Strategy Pattern

1. **Multiple Algorithms**: When you have several related algorithms that differ in behavior
2. **Runtime Selection**: When you need to switch between algorithms at runtime
3. **Algorithm Independence**: When algorithms should be independent of the context that uses them
4. **Hide Implementation**: When you want to hide algorithm implementation details from clients
5. **Eliminate Conditionals**: When you have complex conditional logic for selecting algorithms

### When NOT to Use

1. **Simple Algorithms**: When you have only one algorithm that won't change
2. **Tight Coupling**: When algorithms need access to internal context state
3. **Performance Critical**: When the overhead of virtual calls is unacceptable
4. **Few Algorithms**: When you have only 1-2 algorithms that rarely change

## Important Considerations

### Strategy vs State Pattern

- **Strategy**: Client chooses the strategy, algorithms are independent
- **State**: State transitions are internal, states know about each other

### Strategy vs Template Method

- **Strategy**: Composition-based, runtime algorithm selection
- **Template Method**: Inheritance-based, compile-time algorithm variation

### Performance Considerations

- Virtual function calls have slight overhead
- For performance-critical code, consider alternative approaches
- The flexibility often outweighs the performance cost

### Testing Benefits

```cpp
// Easy to test individual strategies
class TestCompressionStrategy : public CompressionStrategy {
    // Mock implementation for testing
};
```

## Summary

The Strategy Design Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. It lets the algorithm vary independently from clients that use it.

### Key Takeaways:

1. **Algorithm Encapsulation**: Each algorithm is in its own class
2. **Interchangeable**: Strategies can be swapped at runtime
3. **Decoupled**: Context doesn't know strategy implementation details
4. **Eliminates Conditionals**: No complex if-else chains for algorithm selection
5. **Open/Closed**: Easy to add new strategies without modifying existing code

The pattern is particularly valuable when you need to support multiple variations of an algorithm and want to avoid complex conditional logic while maintaining the flexibility to change algorithms at runtime.