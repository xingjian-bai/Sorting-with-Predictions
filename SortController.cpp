#include "SortController.h"
#include <iostream>
#include <iomanip>

using namespace std;

SortController::SortController(SortGame* game): game(game) {}

void SortController::addAlgorithm(SortAlgorithm* algo, std::string name) {
    algorithms.push_back(algo);
    names.push_back(name);
}

vector<int> SortController::runGame(bool verbose) {
    vector<int> result;
    for (int i = 0; i < algorithms.size(); i++) {
        game->clear_counter();
        // cerr << "at " << names[i] << " ";
        std::vector<int> sorted_array = algorithms[i]->sort(*game);

        int columnWidth = 15;
        if (verbose)
            cerr << left << setw(columnWidth) << names[i];

        if (game->isSameAsRank(sorted_array)) {
            if (verbose)
                cerr << "OK! in " << setw(columnWidth - 7) << game->counter() << " steps" << endl;
            result.push_back(game->counter());
        } else {
            cerr << "The sorted array is not the same as rank!" << std::endl;
            game->print();
            cerr << "sorted array: ";
            for (int i = 0; i < sorted_array.size(); i++)
                cerr << sorted_array[i] << " ";
            cerr << endl;
            exit(1);
        }
    }
    return result;
}

