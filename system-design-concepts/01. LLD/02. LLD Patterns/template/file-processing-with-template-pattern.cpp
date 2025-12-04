#include <iostream>
using namespace std;

// Abstract Base Class
class FileProcessor {
public:
    // Template Method
    void processFile() {
        openFile();
        readData();
        processData(); // subclass specific
        closeFile();
    }

    void openFile() { cout << "Opening file...\n"; }
    void readData() { cout << "Reading file data...\n"; }
    void closeFile() { cout << "Closing file...\n"; }

    // To be implemented by subclasses
    virtual void processData() = 0;
};

// Text File Processor
class TextFileProcessor : public FileProcessor {
public:
    void processData() override {
        cout << "Processing plain text data...\n";
    }
};

// CSV File Processor
class CSVFileProcessor : public FileProcessor {
public:
    void processData() override {
        cout << "Processing CSV data into rows/columns...\n";
    }
};

// JSON File Processor
class JSONFileProcessor : public FileProcessor {
public:
    void processData() override {
        cout << "Processing JSON key-value pairs...\n";
    }
};

// Client
int main() {
    cout << "--- Text File ---\n";
    TextFileProcessor textFile;
    textFile.processFile();

    cout << "\n--- CSV File ---\n";
    CSVFileProcessor csvFile;
    csvFile.processFile();

    cout << "\n--- JSON File ---\n";
    JSONFileProcessor jsonFile;
    jsonFile.processFile();

    return 0;
}
