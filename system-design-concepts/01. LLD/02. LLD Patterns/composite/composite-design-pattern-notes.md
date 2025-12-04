# Composite Design Pattern - Complete Guide

## The Problem: Managing Hierarchical Structures

### The Complexity of Tree-like Structures

Imagine you're building a file system manager or a graphic design application. You need to handle objects that can contain other objects:

**File System Example:**
- Directories can contain files AND other directories
- Operations like "get size" or "display" should work on both files and directories
- Without a pattern, you'd need complex conditional logic everywhere

**Graphic Design Example:**
- Simple shapes: Circle, Rectangle
- Complex shapes: Group of shapes
- Operations: Move, Rotate, Scale should work on both individual and grouped shapes

### The Problem Without Composite Pattern

```cpp
// Problematic approach without Composite
class File {
    void display() { /* display file */ }
};

class Directory {
    void display() {
        // Display directory
        for (File* file : files) {
            file->display();
        }
        for (Directory* dir : subdirs) {
            dir->display();  // This won't work easily!
        }
    }
    
    vector<File*> files;
    vector<Directory*> subdirs;  // Different handling needed!
};
```

**Issues:**
- Different handling for files vs directories
- Complex recursive logic
- Client code needs to know object types
- Adding new element types breaks existing code

## The Solution: Composite Design Pattern

### Core Concept

The Composite Pattern allows you to compose objects into tree structures and work with these structures as if they were individual objects.

**Simple Analogy**: 
- Military organization: Squad (composite) contains Soldiers (leaf) AND other Squads (composite)
- Same commands work at all levels: "Attack!" works for soldier or entire army

### The Pattern Structure

![](https://media.geeksforgeeks.org/wp-content/uploads/20250908165326513211/composite_pattern_.webp)

![](https://media.geeksforgeeks.org/wp-content/uploads/20231106201221/Composite-Design-Pattern.jpg)

```
Component (Interface)
    ↑
    |
    +---- Leaf (Implements Component)
    |
    +---- Composite (Implements Component + contains Components)
```

## Step-by-Step Implementation

### 1. Component Interface

The common interface that both leaf and composite objects implement:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Component: Common interface for all objects in the hierarchy
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display() const = 0;
    virtual int getSize() const = 0;
    virtual void addComponent(FileSystemComponent* component) {
        // Default implementation does nothing
        // Overridden only in Composite classes
    }
};
```

### 2. Leaf Class

Represents individual objects that don't have children:

```cpp
// Leaf: Represents individual files
class File : public FileSystemComponent {
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void display() const override {
        std::cout << "File: " << name << " (" << size << " bytes)" << std::endl;
    }
    
    int getSize() const override {
        return size;
    }
    
private:
    std::string name;
    int size;
};
```

### 3. Composite Class

Represents container objects that can hold other components:

```cpp
// Composite: Represents directories that can contain files and other directories
class Directory : public FileSystemComponent {
public:
    Directory(const std::string& name) : name(name) {}
    
    ~Directory() {
        for (auto component : components) {
            delete component;
        }
    }
    
    void display() const override {
        std::cout << "Directory: " << name << " [Total: " << getSize() << " bytes]" << std::endl;
        // Indent for better hierarchy visualization
        for (const auto& component : components) {
            std::cout << "  ";
            component->display();
        }
    }
    
    int getSize() const override {
        int totalSize = 0;
        for (const auto& component : components) {
            totalSize += component->getSize();
        }
        return totalSize;
    }
    
    void addComponent(FileSystemComponent* component) override {
        components.push_back(component);
    }
    
private:
    std::string name;
    std::vector<FileSystemComponent*> components;
};
```

## Complete Working Example

### File System Hierarchy Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Component Interface
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display() const = 0;
    virtual int getSize() const = 0;
    virtual void addComponent(FileSystemComponent* component) {
        // Default empty implementation
    }
};

// Leaf: File
class File : public FileSystemComponent {
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void display() const override {
        std::cout << "File: " << name << " (" << size << " bytes)" << std::endl;
    }
    
    int getSize() const override {
        return size;
    }
    
private:
    std::string name;
    int size;
};

// Composite: Directory
class Directory : public FileSystemComponent {
public:
    Directory(const std::string& name) : name(name) {}
    
    ~Directory() {
        for (auto component : components) {
            delete component;
        }
    }
    
    void display() const override {
        std::cout << "Directory: " << name << " [Total: " << getSize() << " bytes]" << std::endl;
        for (const auto& component : components) {
            std::cout << "  ";
            component->display();
        }
    }
    
    int getSize() const override {
        int totalSize = 0;
        for (const auto& component : components) {
            totalSize += component->getSize();
        }
        return totalSize;
    }
    
    void addComponent(FileSystemComponent* component) override {
        components.push_back(component);
    }
    
private:
    std::string name;
    std::vector<FileSystemComponent*> components;
};

// Client Code
int main() {
    std::cout << "=== File System Hierarchy Example ===" << std::endl;
    
    // Create individual files (Leaf objects)
    FileSystemComponent* file1 = new File("document.txt", 1024);
    FileSystemComponent* file2 = new File("image.jpg", 2048);
    FileSystemComponent* file3 = new File("notes.txt", 512);
    FileSystemComponent* file4 = new File("photo.png", 4096);
    
    // Create directories (Composite objects)
    Directory* documents = new Directory("Documents");
    Directory* pictures = new Directory("Pictures");
    Directory* home = new Directory("Home");
    
    // Build the hierarchy
    documents->addComponent(file1);
    documents->addComponent(file3);
    
    pictures->addComponent(file2);
    pictures->addComponent(file4);
    
    home->addComponent(documents);
    home->addComponent(pictures);
    
    // Display the entire hierarchy
    std::cout << "\nComplete File System Structure:" << std::endl;
    home->display();
    
    // Demonstrate uniform treatment
    std::cout << "\nIndividual Component Sizes:" << std::endl;
    std::cout << "File 1 size: " << file1->getSize() << " bytes" << std::endl;
    std::cout << "Documents folder size: " << documents->getSize() << " bytes" << std::endl;
    std::cout << "Home folder size: " << home->getSize() << " bytes" << std::endl;
    
    // Cleanup
    delete home;  // This will delete the entire hierarchy
    
    return 0;
}
```

### Expected Output:
```
=== File System Hierarchy Example ===

Complete File System Structure:
Directory: Home [Total: 7680 bytes]
  Directory: Documents [Total: 1536 bytes]
    File: document.txt (1024 bytes)
    File: notes.txt (512 bytes)
  Directory: Pictures [Total: 6144 bytes]
    File: image.jpg (2048 bytes)
    File: photo.png (4096 bytes)

Individual Component Sizes:
File 1 size: 1024 bytes
Documents folder size: 1536 bytes
Home folder size: 7680 bytes
```

## Advanced Example: Graphic Design System

```cpp
#include <iostream>
#include <vector>
#include <string>

// Component: Graphic interface
class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void draw() const = 0;
    virtual void move(int x, int y) = 0;
    virtual void add(Graphic* graphic) {
        // Default empty implementation
    }
};

// Leaf: Circle
class Circle : public Graphic {
public:
    Circle(const std::string& name, int x, int y, int radius) 
        : name(name), x(x), y(y), radius(radius) {}
    
    void draw() const override {
        std::cout << "Drawing Circle '" << name << "' at (" << x << "," << y 
                  << ") with radius " << radius << std::endl;
    }
    
    void move(int newX, int newY) override {
        x = newX;
        y = newY;
        std::cout << "Moved Circle '" << name << "' to (" << x << "," << y << ")" << std::endl;
    }
    
private:
    std::string name;
    int x, y, radius;
};

// Leaf: Rectangle
class Rectangle : public Graphic {
public:
    Rectangle(const std::string& name, int x, int y, int width, int height) 
        : name(name), x(x), y(y), width(width), height(height) {}
    
    void draw() const override {
        std::cout << "Drawing Rectangle '" << name << "' at (" << x << "," << y 
                  << ") size " << width << "x" << height << std::endl;
    }
    
    void move(int newX, int newY) override {
        x = newX;
        y = newY;
        std::cout << "Moved Rectangle '" << name << "' to (" << x << "," << y << ")" << std::endl;
    }
    
private:
    std::string name;
    int x, y, width, height;
};

// Composite: GraphicGroup
class GraphicGroup : public Graphic {
public:
    GraphicGroup(const std::string& name) : name(name) {}
    
    ~GraphicGroup() {
        for (auto graphic : graphics) {
            delete graphic;
        }
    }
    
    void draw() const override {
        std::cout << "Drawing Group: " << name << " (contains " << graphics.size() << " graphics)" << std::endl;
        for (const auto& graphic : graphics) {
            std::cout << "  ";
            graphic->draw();
        }
    }
    
    void move(int x, int y) override {
        std::cout << "Moving entire group '" << name << "' by (" << x << "," << y << ")" << std::endl;
        // In real implementation, you'd update all child coordinates
        for (auto& graphic : graphics) {
            graphic->move(x, y);  // This works for both leaves and composites!
        }
    }
    
    void add(Graphic* graphic) override {
        graphics.push_back(graphic);
    }
    
private:
    std::string name;
    std::vector<Graphic*> graphics;
};

// Client code for graphics
void demonstrateGraphics() {
    std::cout << "\n=== Graphic Design System Example ===" << std::endl;
    
    // Create individual shapes
    Graphic* circle1 = new Circle("Red Circle", 10, 10, 5);
    Graphic* circle2 = new Circle("Blue Circle", 30, 20, 8);
    Graphic* rectangle = new Rectangle("Green Rectangle", 50, 60, 15, 10);
    
    // Create groups
    GraphicGroup* circlesGroup = new GraphicGroup("Circles Group");
    GraphicGroup* allShapes = new GraphicGroup("All Shapes");
    
    // Build hierarchy
    circlesGroup->add(circle1);
    circlesGroup->add(circle2);
    
    allShapes->add(circlesGroup);
    allShapes->add(rectangle);
    
    // Demonstrate uniform operations
    std::cout << "\nDrawing individual shape:" << std::endl;
    circle1->draw();
    
    std::cout << "\nDrawing group of shapes:" << std::endl;
    circlesGroup->draw();
    
    std::cout << "\nDrawing entire composition:" << std::endl;
    allShapes->draw();
    
    std::cout << "\nMoving entire composition:" << std::endl;
    allShapes->move(5, 5);
    
    // Cleanup
    delete allShapes;
}
```

## Key Benefits and When to Use

### Benefits

1. **Uniform Treatment**: Client code doesn't need to distinguish between leaf and composite objects
2. **Simplified Client Code**: No complex conditional logic for different object types
3. **Easy to Add New Types**: New component types can be added without changing existing code
4. **Flexible Structure**: Easy to build complex tree structures
5. **Open/Closed Principle**: Open for extension, closed for modification

### When to Use Composite Pattern

1. **Hierarchical Structures**: When you need to represent part-whole hierarchies
2. **Uniform Operations**: When you want to treat individual objects and compositions uniformly
3. **Recursive Behavior**: When operations need to be applied recursively over object trees
4. **Tree Navigation**: When you need to traverse complex object structures

### Common Use Cases

- **File Systems**: Files and directories
- **GUI Components**: Windows containing panels containing buttons
- **Organization Charts**: Departments containing teams containing employees
- **Graphic Editors**: Shapes and groups of shapes
- **Menu Systems**: Menu items and submenus

## Important Considerations

### Memory Management

In the examples, we used raw pointers for simplicity. In production code, consider:

```cpp
// Better approach with smart pointers
class Directory : public FileSystemComponent {
private:
    std::vector<std::unique_ptr<FileSystemComponent>> components;
    
    void addComponent(std::unique_ptr<FileSystemComponent> component) {
        components.push_back(std::move(component));
    }
};
```

### Performance Considerations

- Deep hierarchies can impact performance
- Consider caching computed values (like total size)
- Be mindful of recursion depth

### Design Considerations

1. **Child Management in Component Interface**: 
   - Should `add/remove` methods be in Component interface?
   - Pros: More uniform interface
   - Cons: Leaf classes have empty implementations (violates Interface Segregation)

2. **Type Safety**:
   - Client might try to add children to leaf nodes
   - Options: Throw exception, ignore, or redesign interface

## Summary

The Composite Pattern provides an elegant solution for working with tree-like structures by:

1. **Defining a common interface** for both individual and composite objects
2. **Allowing recursive composition** where composites can contain other composites
3. **Enabling uniform treatment** of simple and complex objects

The pattern is particularly valuable in scenarios where you need to build hierarchical structures and perform operations that should work consistently across all levels of the hierarchy.

The key insight is that by treating individual objects and compositions uniformly, you can write simpler, more maintainable code that works with complex object structures without needing to understand their internal composition.