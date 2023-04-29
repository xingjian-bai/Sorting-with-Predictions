#include "SortAlgo.h"

class HeapSort : public SortAlgorithm {
public:
    // Constructor
    HeapSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to build the max heap
    void buildMaxHeap(SortGame& game, int n, std::vector<int>& indexes);
    // Function to heapify the given subtree rooted at index i
    void heapify(SortGame& game, int n, int i, std::vector<int>& indexes);
    // Function to swap elements at two given indexes
    void swap(int& a, int& b);
};
