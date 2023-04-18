#include "SortController.h"
#include <iostream>

SortController::SortController(SortGame& game, SortAlgorithm& algorithm)
    : game_(game), algorithm_(algorithm) {}

void SortController::runGame() {
    std::vector<int> sorted_array = algorithm_.sort(game_);

    if (game_.isSameAsRank(sorted_array)) {
        // std::cout << "The sorted array is the same as rank!" << std::endl;
    } else {
        std::cout << "The sorted array is not the same as rank!" << std::endl;
        exit(1);
    }
}

