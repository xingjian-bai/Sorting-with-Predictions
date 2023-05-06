#include "settings.h"
#include "Interface.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdio>
#include "../algorithms/Utils.h"
using namespace std;

double random01() {
    return (double)rand() / RAND_MAX;
}

int large_random(int n) {
    return (long long) rand() * rand() % n;
}


void badobject(SortGame *game, int size, double prob) {
    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    for (int i = 0; i < size; i++) {
        A.push_back(i);
        if (random01() <= prob) {
            preds.push_back(rand() % size);
        } else {
            preds.push_back(i);
        }
        ranking.push_back(i);
    }
}

void permuteobject(SortGame *game, int size, double prob) {
    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    vector<int> subset;
    vector<int> permute;
    for (int i = 0; i < size; i++)
        if (random01() <= prob) {
            subset.push_back(i);
            permute.push_back(i);
        }
    
    shuffle(permute.begin(), permute.end(), gen);

    int pter = 0;
    for (int i = 0; i < size; i++)
    {
        A.push_back(i);
        ranking.push_back(i);
        if (pter < subset.size() && subset[pter] == i) {
            preds.push_back(permute[pter]);
            pter++;
        } else {
            preds.push_back(i);
        }
    }
}

void worstobject(SortGame *game, int size) {
    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    vector<int> root[size];
    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
        preds.push_back(size - i - 1);
    }
}

void defaultobject(SortGame *game, int size) {
    mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    vector<int> root[size];
    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
        preds.push_back(i);
    }
}


void countrypopulation(SortGame *game, int old) {

    game->init();
    const string filename = "data/country_population_cleaned.txt";
    auto [row2021, rowOld] = parsePopulationData(filename, old);
    

    A = row2021;

    vector<pair<ll, int>> indexedRowOld;
    for (int i = 0; i < rowOld.size(); i++)         indexedRowOld.push_back(make_pair(rowOld[i], i));
    sort(indexedRowOld.begin(), indexedRowOld.end());
    preds.resize(rowOld.size());
    for (int i = 0; i < indexedRowOld.size(); i++)  preds[indexedRowOld[i].second] = i;

    vector<pair<ll, int>> indexedRowA;
    for (int i = 0; i < row2021.size(); i++)         indexedRowA.push_back(make_pair(A[i], i));
    sort(indexedRowA.begin(), indexedRowA.end());
    ranking.resize(A.size());
    for (int i = 0; i < indexedRowA.size(); i++)  ranking[indexedRowA[i].second] = A[indexedRowA[i].second] = i;
}


void decayobject(SortGame *game, int size, double decay) {
    game->init();

    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
        preds.push_back(i);
    }

    double ratio = log(size) / size;
    // cerr << "error ratio: " << ratio << endl;
    // cerr << "rand01: " << random01() << endl;
    for (int dec = 0; dec < decay * size; dec ++)
        for (int i = 0; i < size; i++) {
            if (random01() <= ratio) {
                // cerr << "happened! " << " " << random01() << endl;
                if (random01() <= 0.5)
                    preds[i] = max(preds[i] - (int)log(size), 0);
                else 
                    preds[i] = min(preds[i] + (int)log(size), size - 1);
            }
            // if (random01() <= ratio) {
            //     preds[i] /= 2;
            // }
            // else {
            //     preds[i] = (preds[i] + size) / 2;
            // }
        }
}

void defaultrelation(SortGame *game, int size) {
    game->init();

    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
    }
    for (int i = 0; i < size; i++) {
        vector <bool> rel_i(size, false);
        for (int j = i + 1; j < size; j ++)
            rel_i[j] = (ranking[i] < ranking[j]);
        rel.push_back(rel_i);
    }
}



void Goodbadrelation(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);

    bool ifBad[size];
    
    for (int i = 0; i < A.size(); i++)
        ifBad[i] = (random01() <= ratio);
    
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (ifBad[i] && ifBad[j]) {
                bool R = (random01() <= 0.5);
                rel[i][j] = R;
                rel[j][i] = !R;
            }
    game->ReltoRank();
}

void Badgoodrelation(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);

    bool ifBad[size];
    
    for (int i = 0; i < A.size(); i++)
        ifBad[i] = (random01() <= ratio);
    
    for (int i = 0; i < A.size(); i++) {
        for (int j = i + 1; j < A.size(); j++)
            if (ifBad[i] || ifBad[j]) {
                bool R = (random01() <= 0.5);
                rel[i][j] = R;
                rel[j][i] = !R;
            }
        ranking[i] = A[i] = i;
    }
    game->ReltoRank();
}