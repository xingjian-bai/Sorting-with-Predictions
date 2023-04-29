#include "SortAlgo.h"

class TimSort : public SortAlgorithm {
public:
    // Constructor
    TimSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes);

    // Main Tim Sort function
    void timSort(SortGame& game, int n, std::vector<int>& indexes);

    // Constants
    const int RUN = 32;
};

