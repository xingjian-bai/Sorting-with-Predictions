#include "SortAlgo.h"

class LeftAlgo : public SortAlgorithm {
public:
    //init functions
    LeftAlgo() = default;

    std::vector<int> sort(SortGame& game) override;
};
