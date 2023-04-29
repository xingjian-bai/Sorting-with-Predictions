#include "SortAlgo.h"

class MergeSort : public SortAlgorithm {
public:
    // Constructor
    MergeSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Recursive merge sort function
    void mergeSort(SortGame& game, int low, int high, std::vector<int>& indexes);
    // Function to merge two sorted subarrays
    void merge(SortGame& game, int low, int mid, int high, std::vector<int>& indexes);
};
