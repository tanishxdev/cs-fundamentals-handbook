

# **Flyweight Design Pattern — Complete Tutorial**

---

## **1. Concept**

### **Definition:**

Flyweight is a **Structural Design Pattern** that helps **reduce memory usage** when you need to create a **large number of similar objects**.

Instead of creating a completely new object every time, we **share common (intrinsic) data** between objects and only store **unique (extrinsic) data** individually.

---

## **2. Intuition — Why This Pattern Exists**

### **Problem Scenario:**

Imagine you are building a **graphics editor** or a **map application** like Google Maps:

* It displays **millions of trees, cars, or icons**.
* Each of these objects has:

  * A **shared part** (e.g., image, shape, type)
  * A **unique part** (e.g., position, rotation, coordinates)

Creating a separate object for every tree will explode memory usage.

So instead, we **share the common parts** and only change what’s unique.

That’s exactly what **Flyweight Pattern** does.

---

## **3. Problem it Solves**

Without Flyweight:

```text
10,000 FolderIcons × 5 KB per object = 50 MB memory
```

With Flyweight:

```text
1 shared FolderIcon (5 KB) + 10,000 coordinates (40 KB) ≈ 45 KB total
```

Huge optimization.

---

## **4. Real-Life Analogies**

| Example         | Shared (Intrinsic) | Unique (Extrinsic)  |
| --------------- | ------------------ | ------------------- |
| **Game Trees**  | Texture, Color     | Coordinates (x, y)  |
| **Text Editor** | Font, Size         | Character position  |
| **UI Icons**    | Image              | Screen position     |
| **Cars on map** | Model, shape       | Latitude, longitude |

---

## **5. Core Components**

![Components](https://media.geeksforgeeks.org/wp-content/uploads/20241025174722819618/fly.jpg)


| Component               | Role                                          |
| ----------------------- | --------------------------------------------- |
| **Flyweight Interface** | Defines method(s) that accept extrinsic data. |
| **Concrete Flyweight**  | Implements shared data and operations.        |
| **Flyweight Factory**   | Creates and manages shared flyweight objects. |
| **Client**              | Uses flyweights and passes extrinsic data.    |

---

## **6. Visual Understanding (UML Flow)**

```
       +----------------------+
       |   FlyweightFactory   |
       +----------------------+
                |
        getFlyweight(type)
                |
     +----------+-----------+
     |                      |
+-----------+         +-----------+
| FileIcon  |         | FolderIcon|
| intrinsic |         | intrinsic |
+-----------+         +-----------+
        ^                     ^
        |                     |
      Client --------------> uses (x, y)
```

---

## **7. Implementation — C++ Version (Step-by-Step with Deep Comments)**

---

### **Step 1: Flyweight Interface**

```cpp
#include <bits/stdc++.h>
using namespace std;

// ============================================
// Step 1: Flyweight Interface
// ============================================
// This defines a common interface for all icons.
// It accepts extrinsic data (like coordinates) in draw() method.
class Icon {
public:
    virtual void draw(int x, int y) = 0;  // abstract draw method
    virtual ~Icon() {}
};
```

---

### **Step 2: Concrete Flyweights (Shared Objects)**

```cpp
// ============================================
// Step 2: Concrete Flyweight - File Icon
// ============================================
class FileIcon : public Icon {
private:
    string type;      // Intrinsic data — same for all file icons
    string imageName; // Intrinsic data — shared image name

public:
    FileIcon(string type, string imageName)
        : type(type), imageName(imageName) {}

    void draw(int x, int y) override {
        // Draw icon using intrinsic + extrinsic state
        cout << "Drawing " << type
             << " file icon (" << imageName
             << ") at position (" << x << ", " << y << ")\n";
    }
};

// ============================================
// Step 3: Concrete Flyweight - Folder Icon
// ============================================
class FolderIcon : public Icon {
private:
    string color;     // Intrinsic data
    string imageName; // Intrinsic data

public:
    FolderIcon(string color, string imageName)
        : color(color), imageName(imageName) {}

    void draw(int x, int y) override {
        cout << "Drawing " << color
             << " folder icon (" << imageName
             << ") at position (" << x << ", " << y << ")\n";
    }
};
```

---

### **Step 3: Flyweight Factory**

```cpp
// ============================================
// Step 4: Flyweight Factory
// ============================================
// Manages creation and sharing of flyweight objects.
// Returns existing object if already created.
class IconFactory {
private:
    unordered_map<string, Icon*> iconCache;  // Cache of flyweight objects

public:
    Icon* getIcon(const string& key) {
        // If already exists → reuse
        if (iconCache.find(key) != iconCache.end()) {
            return iconCache[key];
        }

        // Else create new flyweight
        Icon* icon = nullptr;
        if (key == "file")
            icon = new FileIcon("document", "document.png");
        else if (key == "folder")
            icon = new FolderIcon("blue", "folder.png");
        else
            throw invalid_argument("Unsupported icon type!");

        iconCache[key] = icon;  // Store in cache
        return icon;
    }

    ~IconFactory() {
        // Cleanup cached objects
        for (auto& pair : iconCache)
            delete pair.second;
    }
};
```

---

### **Step 4: Client Code**

```cpp
// ============================================
// Step 5: Client Code
// ============================================
int main() {
    IconFactory factory;  // Create factory

    // Fetch icons — factory decides whether to reuse or create
    Icon* fileIcon1 = factory.getIcon("file");
    Icon* fileIcon2 = factory.getIcon("file"); // will reuse the same FileIcon

    Icon* folderIcon1 = factory.getIcon("folder");
    Icon* folderIcon2 = factory.getIcon("folder"); // reused again

    // Draw icons at different coordinates (extrinsic state)
    fileIcon1->draw(100, 100);
    fileIcon2->draw(200, 150);

    folderIcon1->draw(300, 200);
    folderIcon2->draw(400, 250);

    return 0;
}
```

---

### **Output**

```
Drawing document file icon (document.png) at position (100, 100)
Drawing document file icon (document.png) at position (200, 150)
Drawing blue folder icon (folder.png) at position (300, 200)
Drawing blue folder icon (folder.png) at position (400, 250)
```

---

## **8. Behind the Scenes — Step-by-Step Flow**

| Step | Description                                                           |
| ---- | --------------------------------------------------------------------- |
| 1️⃣  | Client asks `IconFactory` for `"file"`.                               |
| 2️⃣  | Factory checks if `"file"` exists in cache.                           |
| 3️⃣  | If not, it creates `FileIcon` and stores it.                          |
| 4️⃣  | Next time, factory **returns the same instance**.                     |
| 5️⃣  | Client calls `draw(x, y)` with different positions (extrinsic state). |

---

## **9. Key Concept: Intrinsic vs Extrinsic Data**

| Type          | Meaning                                | Example                 |
| ------------- | -------------------------------------- | ----------------------- |
| **Intrinsic** | Shared state — stored inside flyweight | Color, shape, texture   |
| **Extrinsic** | Unique state — passed externally       | x, y position, rotation |

---

## **10. When to Use Flyweight Pattern**

✅ Use it when:

* You need **millions of similar objects**.
* Memory optimization is important.
* Most object data is **common/shared**.
* You can separate **intrinsic and extrinsic state**.

---

## **11. When *Not* to Use It**

❌ Avoid it when:

* Each object’s data is **completely unique**.
* Objects are **mutable** and frequently change.
* System complexity is small — overhead not worth it.

---

## **12. Pros and Cons**

| Pros ✅                         | Cons ❌                               |
| ------------------------------ | ------------------------------------ |
| Saves memory                   | Adds complexity                      |
| Reuses existing objects        | Needs careful state separation       |
| Improves performance           | Debugging shared state can be tricky |
| Ideal for large object systems | Not useful for small data sets       |

---

## **13. Relation to Other Patterns**

| Pattern       | Relationship                                     |
| ------------- | ------------------------------------------------ |
| **Prototype** | Focuses on cloning objects (not sharing)         |
| **Singleton** | Ensures single instance globally, not per key    |
| **Factory**   | Used *inside* Flyweight to manage shared objects |

---

## **14. Real-World Example Summary**

| Domain    | Example                                |
| --------- | -------------------------------------- |
| Games     | Trees, bullets, enemies share textures |
| UI        | Reuse icons, buttons, and labels       |
| Maps      | Cars, markers share same graphic       |
| Documents | Characters share font data             |

---

## **15. Final Takeaways**

> “Flyweight Pattern = **Share common data, store unique data separately.**”

* Helps in **memory optimization**.
* Great for **high-performance, large-scale systems**.
* Think of it like **object pooling for shared state**.

---
