#include <iostream>
using namespace std;

// Strategy Interface
class SortingStrategy {
public:
    virtual void sort(int arr[], int size) = 0;
    virtual ~SortingStrategy() {}
};

// Concrete Strategy 1: Bubble Sort
class BubbleSortStrategy : public SortingStrategy {
public:
    void sort(int arr[], int size) override {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
        cout << "Bubble Sort performed.\n";
    }
};

// Concrete Strategy 2: Quick Sort
class QuickSortStrategy : public SortingStrategy {
public:
    void sort(int arr[], int size) override {
        // Simplified placeholder
        cout << "Quick Sort performed.\n";
    }
};

// Context
class SortingContext {
private:
    SortingStrategy* sortingStrategy;

public:
    SortingContext(SortingStrategy* strategy) : sortingStrategy(strategy) {}
    void setSortingStrategy(SortingStrategy* strategy) { sortingStrategy = strategy; }
    void performSort(int arr[], int size) { sortingStrategy->sort(arr, size); }
};

// Client
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;

    SortingStrategy* bubbleSort = new BubbleSortStrategy();
    SortingContext context(bubbleSort);
    context.performSort(arr, size);

    // Switch strategy at runtime
    SortingStrategy* quickSort = new QuickSortStrategy();
    context.setSortingStrategy(quickSort);
    context.performSort(arr, size);

    delete bubbleSort;
    delete quickSort;
    return 0;
}