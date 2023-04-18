#pragma once
#include "../SortAlgo.h"

class BothAlgo : public SortAlgorithm {
public:
    //init functions
    BothAlgo() = default;

    std::vector<int> sort(SortGame& game) override;
};
