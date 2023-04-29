#pragma once
#include "../settings/Interface.h"
#include <vector>

class SortAlgorithm {
public:
    // 对SortGame中的数字数组A进行排序，并返回排序后的数组
    virtual std::vector<int> sort(SortGame& game) = 0;
};
