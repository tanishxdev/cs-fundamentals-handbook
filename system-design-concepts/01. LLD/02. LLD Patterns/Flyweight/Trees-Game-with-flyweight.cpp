#include <bits/stdc++.h>
using namespace std;

// =====================================
// Shared Flyweight class: TreeType
// =====================================

// Concept Recap (in simple words)

// Imagine a game showing 10,000 trees in a forest.
// Each tree has:

// A shared part (same type, texture, color) → intrinsic state
// A unique part (x, y position) → extrinsic state

// If we create 10,000 Tree objects separately → huge memory.
// So, we reuse shared tree types and only store unique positions.

// This stores *intrinsic* (shared) data like type, color, texture.
class TreeType {
    string name;
    string color;
    string texture;
public:
    TreeType(string n, string c, string t)
        : name(n), color(c), texture(t) {}

    void draw(int x, int y) {
        cout << "Drawing tree [" << name << ", " << color
             << ", " << texture << "] at (" << x << ", " << y << ")\n";
    }
};

// =====================================
// Flyweight Factory: TreeFactory
// =====================================
// Manages creation & caching of TreeType objects.
class TreeFactory {
    static unordered_map<string, TreeType*> treeMap;
public:
    static TreeType* getTreeType(string name, string color, string texture) {
        string key = name + "_" + color + "_" + texture;

        // If tree type already exists → reuse
        if (treeMap.find(key) != treeMap.end())
            return treeMap[key];

        // Else create and store in map
        TreeType* type = new TreeType(name, color, texture);
        treeMap[key] = type;
        return type;
    }

    static void cleanup() {
        for (auto& p : treeMap) delete p.second;
        treeMap.clear();
    }
};
unordered_map<string, TreeType*> TreeFactory::treeMap;

// =====================================
// Context class: Tree
// =====================================
// This stores *extrinsic* data like (x, y) position.
class Tree {
    int x, y;
    TreeType* type; // shared
public:
    Tree(int x, int y, TreeType* t) : x(x), y(y), type(t) {}
    void draw() { type->draw(x, y); }
};

// =====================================
// Client code
// =====================================
int main() {
    vector<Tree*> forest;

    // Reuse same TreeType objects for many trees
    TreeType* oak = TreeFactory::getTreeType("Oak", "Green", "Rough");
    TreeType* pine = TreeFactory::getTreeType("Pine", "DarkGreen", "Smooth");

    // Create many trees with shared data
    forest.push_back(new Tree(10, 20, oak));
    forest.push_back(new Tree(15, 25, oak));
    forest.push_back(new Tree(30, 35, pine));
    forest.push_back(new Tree(40, 45, pine));

    // Draw all trees
    for (auto tree : forest) tree->draw();

    // Cleanup
    for (auto tree : forest) delete tree;
    TreeFactory::cleanup();

    return 0;
}

// Concepts Summary
// | Term                  | Meaning                                     | Example                   |
// | --------------------- | ------------------------------------------- | ------------------------- |
// | **Intrinsic State**   | Shared data stored inside flyweight         | Tree name, color, texture |
// | **Extrinsic State**   | Unique data passed externally               | Tree position (x, y)      |
// | **Flyweight Factory** | Manages cache of shared objects             | TreeFactory               |
// | **Client**            | Uses flyweights and supplies extrinsic data | Forest (main)             |

// Why Flyweight Helps
// Without Flyweight:
// 10,000 trees × 5KB each = 50MB

// With Flyweight (shared tree types):
// 2 tree types (10KB) + 10,000 positions (≈80KB) ≈ 90KB total
// → 99% memory saved!

// Real-Life Analogy
// Same car model (shared specs), but many cars with unique license plates.
// Same font style shared by all text in a document, but each character has a unique position.