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
        // cerr << "in controller.runGame, enum algos, at " << names[i] << " " << endl;
        // cerr << names[i] << " " << "at the start" << game->counter() << endl;
        double start_time = TIME;
        algorithms[i]->sort(*game);
        double end_time = TIME;
        // cerr << "at the end" << game->counter() << endl;

        if (verbose)
            cerr << left << setw(15) << names[i];

        if (game->isSameAsRank(output_rank)) {
            if (verbose) {
                cerr << "OK! in " << setw(10) << game->counter() << " steps";
                cerr << "Time: " << setw(10) << end_time - start_time << " secs" << endl;
            }
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
