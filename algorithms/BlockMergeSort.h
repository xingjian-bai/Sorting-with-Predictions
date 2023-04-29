#include "SortAlgo.h"

class BlockMergeSort : public SortAlgorithm {
public:
    // Constructor
    BlockMergeSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to find the minimum run length
    int calcMinRun(int n);

    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes);

    // Main Block Merge Sort function
    void blockMergeSort(SortGame& game, int n, std::vector<int>& indexes);
};