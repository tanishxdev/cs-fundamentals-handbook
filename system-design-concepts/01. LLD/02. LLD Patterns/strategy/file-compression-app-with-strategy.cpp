#include <iostream>
#include <string>
using namespace std;

// Strategy Interface
class CompressionStrategy {
public:
    virtual void compress(const string& filePath) = 0;
    virtual ~CompressionStrategy() {}
};

// Concrete Strategy 1: ZIP Compression (placeholder)
class ZipCompressionStrategy : public CompressionStrategy {
public:
    void compress(const string& filePath) override {
        // In real code: Use zlib or minizip library to create .zip file
        cout << "Compressing " << filePath << " using ZIP algorithm.\\n";
    }
};

// Concrete Strategy 2: GZIP Compression (placeholder)
class GzipCompressionStrategy : public CompressionStrategy {
public:
    void compress(const string& filePath) override {
        // In real code: Use zlib to create .gz file
        cout << "Compressing " << filePath << " using GZIP algorithm.\\n";
    }
};

// Concrete Strategy 3: No Compression
class NoCompressionStrategy : public CompressionStrategy {
public:
    void compress(const string& filePath) override {
        cout << "No compression applied to " << filePath << ".\\n";
    }
};

// Context
class CompressionContext {
private:
    CompressionStrategy* compressionStrategy;

public:
    CompressionContext(CompressionStrategy* strategy) : compressionStrategy(strategy) {}
    void setCompressionStrategy(CompressionStrategy* strategy) { compressionStrategy = strategy; }
    void performCompression(const string& filePath) { compressionStrategy->compress(filePath); }
};

// Client
int main() {
    string filePath = "example.txt";

    CompressionStrategy* zipStrategy = new ZipCompressionStrategy();
    CompressionContext context(zipStrategy);
    context.performCompression(filePath);

    // Switch strategy at runtime
    CompressionStrategy* gzipStrategy = new GzipCompressionStrategy();
    context.setCompressionStrategy(gzipStrategy);
    context.performCompression(filePath);

    // Another switch
    CompressionStrategy* noCompress = new NoCompressionStrategy();
    context.setCompressionStrategy(noCompress);
    context.performCompression(filePath);

    delete zipStrategy;
    delete gzipStrategy;
    delete noCompress;
    return 0;
}
