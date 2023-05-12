#include "SortController.h"

#include <iostream>
#include <iomanip>

using namespace std;
#define TIME (double)clock() / CLOCKS_PER_SEC

SortController::SortController(SortGame* game): game(game) {}

void SortController::addAlgorithm(SortAlgorithm* algo, std::string name) {
    algorithms.push_back(algo);
    names.push_back(name);
}

typedef long long ll;
vector<ll> SortController::runGame(bool verbose)
{
    vector<ll> result;
    for (int i = 0; i < algorithms.size(); i++) {
        game->clear_counter();
        output_rank.clear();
        // cerr << "at " << names[i] << " " << endl;
        // cerr << names[i] << " " << "at the start" << game->counter() << endl;
        algorithms[i]->sort(*game);
        // cerr << "at the end" << game->counter() << endl;

        int columnWidth = 15;
        if (verbose)
            cerr << left << setw(columnWidth) << names[i];

        if (game->isSameAsRank(output_rank)) {
            if (verbose)
                cerr << "OK! in " << setw(columnWidth - 7) << game->counter() << " steps" << endl;
            result.push_back(game->counter());
        } else {
            cerr << "The sorted array is not the same as rank!" << std::endl;
            game->print();
            cerr << "sorted array: ";
            for (int i = 0; i < output_rank.size(); i++)
                cerr << output_rank[i] << " ";
            cerr << endl;
            exit(1);
        }
    }
    return result;
}
