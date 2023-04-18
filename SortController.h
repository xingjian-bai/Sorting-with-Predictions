#pragma once
#include "Interface.h"
#include "SortAlgo.h"

class SortController {
public:
    SortController(SortGame& game, SortAlgorithm& algorithm);

    void runGame();

private:
    SortGame& game_;
    SortAlgorithm& algorithm_;
};
