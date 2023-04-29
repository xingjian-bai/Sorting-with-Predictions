#include "SortAlgo.h"

class LIS : public SortAlgorithm {
public:
    //init functions
    LIS() = default;

    std::vector<int> sort(SortGame& game) override;
};
