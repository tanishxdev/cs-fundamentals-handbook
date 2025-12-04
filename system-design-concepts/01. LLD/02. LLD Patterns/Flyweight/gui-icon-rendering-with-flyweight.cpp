#include <bits/stdc++.h>
using namespace std;

// ===============================================================
// Flyweight Design Pattern Example — GUI Icon Rendering System
// ===============================================================
//
// Problem:
//  - We need to draw thousands of icons (file, folder, etc.)
//  - Each icon shares common properties like image, color.
//  - Only position (x, y) differs per icon.
//
// Goal:
//  - Reuse shared (intrinsic) data.
//  - Store unique (extrinsic) data externally.
// ===============================================================


// ============================================
// Step 1: Flyweight Interface
// ============================================
// Defines the standard interface (draw) for all flyweight objects.
class Icon {
public:
    virtual void draw(int x, int y) = 0;  // Draw using extrinsic data (x, y)
    virtual ~Icon() {}
};


// ============================================
// Step 2: Concrete Flyweight - File Icon
// ============================================
// Holds intrinsic (shared) data such as file type and image.
class FileIcon : public Icon {
private:
    string type;       // Intrinsic state — common across all file icons
    string imageName;  // Intrinsic state — shared image name

public:
    FileIcon(string type, string imageName)
        : type(type), imageName(imageName) {}

    void draw(int x, int y) override {
        // Extrinsic data (x, y) passed from client
        cout << "Drawing " << type
             << " file icon (" << imageName
             << ") at position (" << x << ", " << y << ")\n";
    }
};


// ============================================
// Step 3: Concrete Flyweight - Folder Icon
// ============================================
// Holds intrinsic (shared) data such as folder color and image.
class FolderIcon : public Icon {
private:
    string color;      // Intrinsic state — common color for all folders
    string imageName;  // Intrinsic state — shared image name

public:
    FolderIcon(string color, string imageName)
        : color(color), imageName(imageName) {}

    void draw(int x, int y) override {
        cout << "Drawing " << color
             << " folder icon (" << imageName
             << ") at position (" << x << ", " << y << ")\n";
    }
};


// ============================================
// Step 4: Flyweight Factory
// ============================================
// Manages creation and sharing of flyweight objects.
// Returns existing object if already in cache.
class IconFactory {
private:
    unordered_map<string, Icon*> iconCache;  // Cache: type → flyweight object

public:
    Icon* getIcon(const string& key) {
        // If exists → reuse shared object
        if (iconCache.find(key) != iconCache.end()) {
            return iconCache[key];
        }

        // Else create a new one and cache it
        Icon* icon = nullptr;
        if (key == "file")
            icon = new FileIcon("document", "document.png");
        else if (key == "folder")
            icon = new FolderIcon("blue", "folder.png");
        else
            throw invalid_argument("Unsupported icon type: " + key);

        iconCache[key] = icon;
        return icon;
    }

    // Destructor: clean up cached objects
    ~IconFactory() {
        for (auto& pair : iconCache)
            delete pair.second;
    }
};


// ============================================
// Step 5: Client Code
// ============================================
// The client requests icons from factory instead of creating new ones.
// Each draw() call passes extrinsic data like position (x, y).
int main() {
    IconFactory factory;  // Create flyweight factory

    // Request icons — factory manages reuse internally
    Icon* fileIcon1 = factory.getIcon("file");
    Icon* fileIcon2 = factory.getIcon("file");    // Reused
    Icon* folderIcon1 = factory.getIcon("folder");
    Icon* folderIcon2 = factory.getIcon("folder"); // Reused

    // Draw icons with unique coordinates (extrinsic state)
    fileIcon1->draw(100, 100);
    fileIcon2->draw(200, 150);

    folderIcon1->draw(300, 200);
    folderIcon2->draw(400, 250);

    return 0;
}
