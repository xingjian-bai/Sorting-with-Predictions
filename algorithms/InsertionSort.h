#include "SortAlgo.h"

class InsertionSort : public SortAlgorithm {
public:
    //init functions
    InsertionSort() = default;

    std::vector<int> sort(SortGame& game) override;
};
