#include "SortController.h"
#include <iostream>

using namespace std;

SortController::SortController(SortGame* game): game(game) {}

void SortController::addAlgorithm(SortAlgorithm* algo, std::string name) {
    algorithms.push_back(algo);
    names.push_back(name);
}

void SortController::runGame() {
    for (int i = 0; i < algorithms.size(); i++) {
        
        game->clear_counter();
        
        std::vector<int> sorted_array = algorithms[i]->sort(*game);
        if (game->isSameAsRank(sorted_array)) {
            cout << names[i] <<" OK! in " << game->counter() << " steps" << endl;
        } 
        else {
            std::cout << names[i] << "The sorted array is not the same as rank!" << std::endl;
            //output both sorted_array and rank
            for (int i = 0; i < sorted_array.size(); i++) {
                std::cout << sorted_array[i] << " ";
            }
            std::cout << std::endl;
            game->output_rank();
            exit(1);
        }
    }
}

