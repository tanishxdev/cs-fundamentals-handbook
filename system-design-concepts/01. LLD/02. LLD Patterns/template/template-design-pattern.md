
# Template Method Design Pattern - Complete Guide
![](https://media.geeksforgeeks.org/wp-content/uploads/20250913174017828593/Template-Design-Pattern.webp)

## The Problem: Algorithm Structure with Variations

### The Common Algorithm Problem

Imagine you're building a system that processes different types of documents:

- PDF documents
- Word documents
- Text documents

Each document type has a similar processing workflow:
1. Open document
2. Read content
3. Parse content
4. Process data
5. Close document

But the implementation details differ for each document type.

### The Problem Without Template Method

```cpp
// Problematic approach without Template Method
class PDFProcessor {
public:
    void process() {
        openPDF();
        readPDFContent();
        parsePDF();
        processData();
        closePDF();
    }
    
private:
    void openPDF() { /* PDF-specific */ }
    void readPDFContent() { /* PDF-specific */ }
    void parsePDF() { /* PDF-specific */ }
    void processData() { /* common */ }
    void closePDF() { /* PDF-specific */ }
};

class WordProcessor {
public:
    void process() {
        openWord();
        readWordContent();
        parseWord();
        processData();
        closeWord();
    }
    
private:
    void openWord() { /* Word-specific */ }
    void readWordContent() { /* Word-specific */ }
    void parseWord() { /* Word-specific */ }
    void processData() { /* common */ }
    void closeWord() { /* Word-specific */ }
};
```

**Problems:**
1. **Code Duplication**: Common steps repeated across classes
2. **Maintenance Nightmare**: Changing algorithm requires updating all classes
3. **Inconsistent Behavior**: Easy to introduce variations in algorithm flow
4. **No Enforcement**: Nothing prevents subclasses from changing algorithm structure

## The Solution: Template Method Pattern
![](https://media.geeksforgeeks.org/wp-content/uploads/20240213124632/TemplateMethodComponent-(1).webp)
### Core Concept

The Template Method pattern defines the skeleton of an algorithm in a base class but lets subclasses override specific steps without changing the algorithm's structure.

**Simple Analogy**: 
- Recipe book: Same steps for all cakes (mix, bake, cool, decorate)
- Different cakes: Customize ingredients and decoration
- Structure remains the same

## Step-by-Step Implementation

### Basic Structure

```
Abstract Class
    ↑
    |
    +---- Concrete Class A (implements specific steps)
    |
    +---- Concrete Class B (implements specific steps)
```

### 1. Abstract Base Class

Defines the template method and algorithm structure:

```cpp
#include <iostream>
#include <memory>

// Abstract base class defining the template method
class DocumentProcessor {
public:
    virtual ~DocumentProcessor() = default;
    
    // Template Method - defines the algorithm skeleton
    // Made final to prevent subclasses from changing algorithm structure
    void processDocument() {
        openDocument();
        readContent();
        parseContent();
        processData();
        closeDocument();
        postProcess();  // Hook method - optional step
    }
    
protected:
    // Abstract methods - must be implemented by subclasses
    virtual void openDocument() = 0;
    virtual void readContent() = 0;
    virtual void parseContent() = 0;
    virtual void closeDocument() = 0;
    
    // Common implementation - can be overridden if needed
    virtual void processData() {
        std::cout << "Processing data (common implementation)" << std::endl;
    }
    
    // Hook method - optional step, subclasses can override
    virtual void postProcess() {
        // Default empty implementation
    }
};
```

### 2. Concrete Implementations

Implement specific steps while inheriting the algorithm structure:

```cpp
// Concrete class for PDF documents
class PDFProcessor : public DocumentProcessor {
protected:
    void openDocument() override {
        std::cout << "PDF: Opening PDF document" << std::endl;
    }
    
    void readContent() override {
        std::cout << "PDF: Extracting text from PDF" << std::endl;
    }
    
    void parseContent() override {
        std::cout << "PDF: Parsing PDF structure and metadata" << std::endl;
    }
    
    void closeDocument() override {
        std::cout << "PDF: Closing PDF document" << std::endl;
    }
    
    // Override hook method for PDF-specific post-processing
    void postProcess() override {
        std::cout << "PDF: Optimizing PDF for web view" << std::endl;
    }
};

// Concrete class for Word documents
class WordProcessor : public DocumentProcessor {
protected:
    void openDocument() override {
        std::cout << "Word: Opening Word document" << std::endl;
    }
    
    void readContent() override {
        std::cout << "Word: Reading Word document content" << std::endl;
    }
    
    void parseContent() override {
        std::cout << "Word: Parsing Word styles and formatting" << std::endl;
    }
    
    void closeDocument() override {
        std::cout << "Word: Closing Word document" << std::endl;
    }
    
    // Override common method for Word-specific processing
    void processData() override {
        std::cout << "Word: Processing Word-specific data and formatting" << std::endl;
    }
};

// Concrete class for Text documents
class TextProcessor : public DocumentProcessor {
protected:
    void openDocument() override {
        std::cout << "Text: Opening text file" << std::endl;
    }
    
    void readContent() override {
        std::cout << "Text: Reading plain text content" << std::endl;
    }
    
    void parseContent() override {
        std::cout << "Text: Parsing text lines and encoding" << std::endl;
    }
    
    void closeDocument() override {
        std::cout << "Text: Closing text file" << std::endl;
    }
};
```

### 3. Client Code

```cpp
// Client code using the template method
void demonstrateDocumentProcessing() {
    std::cout << "=== Document Processing with Template Method ===" << std::endl;
    
    PDFProcessor pdfProcessor;
    WordProcessor wordProcessor;
    TextProcessor textProcessor;
    
    std::cout << "\n--- Processing PDF Document ---" << std::endl;
    pdfProcessor.processDocument();
    
    std::cout << "\n--- Processing Word Document ---" << std::endl;
    wordProcessor.processDocument();
    
    std::cout << "\n--- Processing Text Document ---" << std::endl;
    textProcessor.processDocument();
}
```

## Complete Beverage Maker Example

### Problem: Different Beverage Preparation

Let's implement the beverage maker example from the problem statement:

```cpp
#include <iostream>
#include <memory>
#include <string>

// Abstract base class for beverage makers
class BeverageMaker {
public:
    virtual ~BeverageMaker() = default;
    
    // Template Method - defines the beverage preparation algorithm
    void makeBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
        serveBeverage();  // Hook method
    }
    
    // Common implementation
    void boilWater() {
        std::cout << "Boiling water" << std::endl;
    }
    
    void pourInCup() {
        std::cout << "Pouring into cup" << std::endl;
    }
    
protected:
    // Abstract methods - must be implemented by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    
    // Hook method - optional, can be overridden
    virtual void serveBeverage() {
        std::cout << "Serving beverage" << std::endl;
    }
};

// Concrete class for Tea
class TeaMaker : public BeverageMaker {
protected:
    void brew() override {
        std::cout << "Steeping the tea" << std::endl;
    }
    
    void addCondiments() override {
        std::cout << "Adding lemon" << std::endl;
    }
    
    // Override hook method for tea-specific serving
    void serveBeverage() override {
        std::cout << "Serving tea with a saucer" << std::endl;
    }
};

// Concrete class for Coffee
class CoffeeMaker : public BeverageMaker {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter" << std::endl;
    }
    
    void addCondiments() override {
        std::cout << "Adding sugar and milk" << std::endl;
    }
    
    // Override hook method for coffee-specific serving
    void serveBeverage() override {
        std::cout << "Serving coffee in a mug" << std::endl;
    }
};

// Concrete class for Hot Chocolate
class HotChocolateMaker : public BeverageMaker {
protected:
    void brew() override {
        std::cout << "Mixing chocolate powder with hot water" << std::endl;
    }
    
    void addCondiments() override {
        std::cout << "Adding marshmallows" << std::endl;
    }
    
    // Hot chocolate doesn't need brewing in the same way
    // So we override boilWater to be more specific
    void boilWater() {
        std::cout << "Heating milk for hot chocolate" << std::endl;
    }
};

// Client code
void demonstrateBeverageMaker() {
    std::cout << "=== Beverage Maker with Template Method ===" << std::endl;
    
    TeaMaker teaMaker;
    CoffeeMaker coffeeMaker;
    HotChocolateMaker hotChocolateMaker;
    
    std::cout << "\n--- Making Tea ---" << std::endl;
    teaMaker.makeBeverage();
    
    std::cout << "\n--- Making Coffee ---" << std::endl;
    coffeeMaker.makeBeverage();
    
    std::cout << "\n--- Making Hot Chocolate ---" << std::endl;
    hotChocolateMaker.makeBeverage();
}
```

## Advanced Example: Data Export System

### Complex Data Export with Template Method

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Data structure
struct DataRecord {
    int id;
    std::string name;
    double value;
    
    DataRecord(int i, const std::string& n, double v) 
        : id(i), name(n), value(v) {}
};

// Abstract base class for data exporters
class DataExporter {
public:
    virtual ~DataExporter() = default;
    
    // Template Method - defines the export algorithm
    void exportData(const std::vector<DataRecord>& data) {
        std::cout << "=== Starting Data Export ===" << std::endl;
        
        validateData(data);
        openConnection();
        prepareExport();
        
        for (const auto& record : data) {
            processRecord(record);
        }
        
        finalizeExport();
        closeConnection();
        notifyCompletion();  // Hook method
        
        std::cout << "=== Export Completed ===" << std::endl;
    }
    
protected:
    // Common implementation
    void validateData(const std::vector<DataRecord>& data) {
        std::cout << "Validating " << data.size() << " records" << std::endl;
        if (data.empty()) {
            throw std::runtime_error("No data to export");
        }
    }
    
    // Abstract methods - must be implemented by subclasses
    virtual void openConnection() = 0;
    virtual void prepareExport() = 0;
    virtual void processRecord(const DataRecord& record) = 0;
    virtual void finalizeExport() = 0;
    virtual void closeConnection() = 0;
    
    // Hook method - optional notification
    virtual void notifyCompletion() {
        std::cout << "Export completed successfully" << std::endl;
    }
};

// Concrete class for CSV export
class CSVExporter : public DataExporter {
protected:
    void openConnection() override {
        std::cout << "CSV: Opening file for writing" << std::endl;
    }
    
    void prepareExport() override {
        std::cout << "CSV: Writing CSV header" << std::endl;
    }
    
    void processRecord(const DataRecord& record) override {
        std::cout << "CSV: Writing record - " 
                  << record.id << ", " << record.name << ", " << record.value << std::endl;
    }
    
    void finalizeExport() override {
        std::cout << "CSV: Finalizing CSV file" << std::endl;
    }
    
    void closeConnection() override {
        std::cout << "CSV: Closing file" << std::endl;
    }
};

// Concrete class for JSON export
class JSONExporter : public DataExporter {
protected:
    void openConnection() override {
        std::cout << "JSON: Opening file for writing" << std::endl;
    }
    
    void prepareExport() override {
        std::cout << "JSON: Starting JSON array" << std::endl;
    }
    
    void processRecord(const DataRecord& record) override {
        std::cout << "JSON: Adding JSON object - " 
                  << "{" << record.id << ", \"" << record.name << "\", " << record.value << "}" << std::endl;
    }
    
    void finalizeExport() override {
        std::cout << "JSON: Closing JSON array" << std::endl;
    }
    
    void closeConnection() override {
        std::cout << "JSON: Closing file" << std::endl;
    }
    
    // Override hook method for JSON-specific notification
    void notifyCompletion() override {
        std::cout << "JSON export completed. File is ready for API consumption." << std::endl;
    }
};

// Concrete class for Database export
class DatabaseExporter : public DataExporter {
protected:
    void openConnection() override {
        std::cout << "Database: Connecting to database" << std::endl;
    }
    
    void prepareExport() override {
        std::cout << "Database: Starting transaction" << std::endl;
    }
    
    void processRecord(const DataRecord& record) override {
        std::cout << "Database: Inserting record into table - " 
                  << record.id << ", " << record.name << std::endl;
    }
    
    void finalizeExport() override {
        std::cout << "Database: Committing transaction" << std::endl;
    }
    
    void closeConnection() override {
        std::cout << "Database: Closing database connection" << std::endl;
    }
    
    // Override validation for database-specific checks
    void validateData(const std::vector<DataRecord>& data) override {
        DataExporter::validateData(data);
        std::cout << "Database: Checking for duplicate IDs" << std::endl;
    }
};

// Client code for data export
void demonstrateDataExport() {
    std::cout << "=== Data Export with Template Method ===" << std::endl;
    
    // Sample data
    std::vector<DataRecord> data = {
        {1, "Alice", 100.5},
        {2, "Bob", 200.3},
        {3, "Charlie", 150.7}
    };
    
    CSVExporter csvExporter;
    JSONExporter jsonExporter;
    DatabaseExporter dbExporter;
    
    std::cout << "\n--- Exporting to CSV ---" << std::endl;
    csvExporter.exportData(data);
    
    std::cout << "\n--- Exporting to JSON ---" << std::endl;
    jsonExporter.exportData(data);
    
    std::cout << "\n--- Exporting to Database ---" << std::endl;
    dbExporter.exportData(data);
}
```

## Real-World Example: Game Development

### Game Loop with Template Method

```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// Abstract base class for games
class Game {
public:
    virtual ~Game() = default;
    
    // Template Method - defines the game loop
    void runGame() {
        initialize();
        
        while (!isGameOver()) {
            processInput();
            update();
            render();
            maintainFrameRate();  // Hook method
        }
        
        cleanup();
        showGameOver();  // Hook method
    }
    
protected:
    // Common implementation
    void initialize() {
        std::cout << "Initializing game..." << std::endl;
        loadResources();
        setupScene();
    }
    
    void cleanup() {
        std::cout << "Cleaning up game resources..." << std::endl;
    }
    
    void maintainFrameRate() {
        // Default: 60 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    
    // Abstract methods - must be implemented by subclasses
    virtual void loadResources() = 0;
    virtual void setupScene() = 0;
    virtual bool isGameOver() = 0;
    virtual void processInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    
    // Hook methods - optional
    virtual void showGameOver() {
        std::cout << "Game Over!" << std::endl;
    }
};

// Concrete class for RPG Game
class RPGGame : public Game {
private:
    int frameCount = 0;
    
protected:
    void loadResources() override {
        std::cout << "RPG: Loading character models, textures, and quest data..." << std::endl;
    }
    
    void setupScene() override {
        std::cout << "RPG: Setting up game world, NPCs, and quests..." << std::endl;
    }
    
    bool isGameOver() override {
        return frameCount >= 5;  // Simulate 5 frames for demo
    }
    
    void processInput() override {
        std::cout << "RPG: Processing player input (movement, combat, dialogue)..." << std::endl;
    }
    
    void update() override {
        std::cout << "RPG: Updating game state (AI, physics, quest progress)..." << std::endl;
        frameCount++;
    }
    
    void render() override {
        std::cout << "RPG: Rendering 3D world, characters, and UI..." << std::endl;
    }
    
    // Override hook method for RPG-specific game over
    void showGameOver() override {
        std::cout << "RPG: The hero's journey has ended. Final score: " << (frameCount * 100) << std::endl;
    }
};

// Concrete class for Puzzle Game
class PuzzleGame : public Game {
private:
    int frameCount = 0;
    
protected:
    void loadResources() override {
        std::cout << "Puzzle: Loading puzzle assets, sound effects, and levels..." << std::endl;
    }
    
    void setupScene() override {
        std::cout << "Puzzle: Setting up game board and initial puzzle state..." << std::endl;
    }
    
    bool isGameOver() override {
        return frameCount >= 3;  // Simulate 3 frames for demo
    }
    
    void processInput() override {
        std::cout << "Puzzle: Processing touch/swipe input for puzzle pieces..." << std::endl;
    }
    
    void update() override {
        std::cout << "Puzzle: Updating puzzle state, checking for solutions..." << std::endl;
        frameCount++;
    }
    
    void render() override {
        std::cout << "Puzzle: Rendering 2D puzzle board and pieces..." << std::endl;
    }
    
    // Override frame rate for smoother puzzle gameplay
    void maintainFrameRate() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(33));  // ~30 FPS
    }
};

// Client code for game loop
void demonstrateGameLoop() {
    std::cout << "=== Game Loop with Template Method ===" << std::endl;
    
    RPGGame rpgGame;
    PuzzleGame puzzleGame;
    
    std::cout << "\n--- Running RPG Game ---" << std::endl;
    rpgGame.runGame();
    
    std::cout << "\n--- Running Puzzle Game ---" << std::endl;
    puzzleGame.runGame();
}
```

## Main Function with All Examples

```cpp
int main() {
    std::cout << "TEMPLATE METHOD DESIGN PATTERN DEMONSTRATIONS" << std::endl;
    std::cout << "============================================" << std::endl;
    
    demonstrateDocumentProcessing();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateBeverageMaker();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateDataExport();
    std::cout << "\n" << std::string(50, '=') << std::endl;
    
    demonstrateGameLoop();
    
    std::cout << "\n=== All demonstrations completed ===" << std::endl;
    return 0;
}
```

## Key Benefits and When to Use

### Benefits

1. **Code Reuse**: Common algorithm structure defined once
2. **Eliminates Duplication**: No repeated algorithm flow across classes
3. **Enforced Structure**: Template method ensures consistent algorithm execution
4. **Flexibility**: Subclasses can customize specific steps
5. **Hollywood Principle**: "Don't call us, we'll call you" - base class calls subclass methods

### When to Use Template Method Pattern

1. **Common Algorithm**: When multiple classes share the same algorithm structure
2. **Code Reuse**: When you want to avoid duplicating algorithm flow
3. **Framework Development**: When building frameworks that users extend
4. **Controlled Extension**: When you want to control how subclasses extend functionality
5. **Hook Methods**: When you need optional steps in an algorithm

### When NOT to Use

1. **Frequent Algorithm Changes**: When algorithm structure changes often
2. **Many Variations**: When most steps need customization in most subclasses
3. **Complex Conditionals**: When algorithm flow depends on complex runtime conditions
4. **Performance Critical**: When the virtual method overhead is unacceptable

## Important Considerations

### Template Method vs Strategy Pattern

- **Template Method**: Inheritance-based, defines algorithm skeleton
- **Strategy**: Composition-based, interchangeable algorithms

### Hook Methods

Hook methods provide extension points:
- **Abstract Methods**: Must be implemented
- **Virtual Methods**: Can be overridden
- **Empty Hook Methods**: Optional extension points

### Preventing Algorithm Modification

Make template method `final` to prevent subclasses from changing algorithm structure:

```cpp
class Base {
public:
    // Prevent subclasses from changing algorithm
    final void templateMethod() {
        step1();
        step2();
        step3();
    }
    
protected:
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() = 0;
};
```

## Summary

The Template Method Design Pattern defines the skeleton of an algorithm in a base class while allowing subclasses to override specific steps without changing the algorithm's structure.

### Key Takeaways:

1. **Algorithm Skeleton**: Base class defines the algorithm flow
2. **Customizable Steps**: Subclasses implement specific steps
3. **Code Reuse**: Common structure eliminates duplication
4. **Controlled Extension**: Framework controls when subclass methods are called
5. **Hook Methods**: Provide optional extension points

The pattern is particularly valuable when you have multiple classes that share the same algorithm structure but differ in the implementation of specific steps. It promotes code reuse, reduces duplication, and ensures consistent algorithm execution across different implementations.