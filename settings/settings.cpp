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

void defaultobject(SortGame *game, int size) {
    // mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
        preds.push_back(i);
    }
    game->RanktoRel();
}


void countrypopulation(SortGame *game, int old) {
    game->init();
    const string filename = "data/country_population_cleaned.txt";
    auto [row2021, rowOld] = parsePopulationData(filename, old);
    

    A = row2021;
    vector<pair<ll, int>> indexedRowOld;
    for (int i = 0; i < rowOld.size(); i++)
        indexedRowOld.push_back(make_pair(rowOld[i], i));
    sort(indexedRowOld.begin(), indexedRowOld.end());
    
    vector<int> helper(rowOld.size());

    for (int i = 0; i < indexedRowOld.size(); i++)
        helper[indexedRowOld[i].second] = i;

    vector<pair<ll, int>> indexedRowA;
    for (int i = 0; i < row2021.size(); i++)
        indexedRowA.push_back(make_pair(A[i], i));
    sort(indexedRowA.begin(), indexedRowA.end());

    ranking.resize(A.size());
    preds.resize(A.size());
    for (int i = 0; i < indexedRowA.size(); i++) {
        // move original index indexedRowA[i].second to position i
        ranking[i] = A[i] = i;
        preds[i] = helper[indexedRowA[i].second];
    }

    game->RanktoRel();
}

void new_object_setting(SortGame *game, int size, double ratio) {
    defaultobject(game, size);

    int number = ratio * size * 0.01;
    cout << "number: " << number << endl;
    for (int i = 0; i < number; i++) {
        int pos = size - 1 - rand() % (size / 2);
        int pred = rand() % (size / 2);
        preds[pos] = pred;
    }


    game->RanktoRel();
}

void swap_and_noise(SortGame *game, int size, double ratio) {
    defaultobject(game, size);

    // swap adjacent
    for (int i = 0; i < size - 1; i++)
        if (random01() <= ratio / 2) {
            swap(preds[i], preds[i + 1]);
        }

    int number = ratio * size * 0.001;
    for (int i = 0; i < number; i++) {
        int pos1 = rand() % size;
        preds[pos1] = rand() % size;
    }

    game->RanktoRel();
}

void decayobject2(SortGame *game, int size, double decay) {
    defaultobject(game, size);
    int length = sqrt(size);
    for (int i = 1; i <= decay * size * length; i ++)
    {
        int pos = rand() % size;
        if (random01() <= 0.5)
            preds[pos] = max(preds[pos] - 1, 0);
        else
            preds[pos] = min(preds[pos] + 1, size - 1);
    }

    game->RanktoRel();
}

void decayobject2_1000(SortGame *game, int size, double decay) {
    defaultobject(game, size);
    for (int i = 1; i <= decay * size * 1000; i ++)
    {
        int pos = rand() % size;
        if (random01() <= 0.5)
            preds[pos] = max(preds[pos] - 1, 0);
        else
            preds[pos] = min(preds[pos] + 1, size - 1);
    }

    game->RanktoRel();
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
            rel_i[j] = 1;
        rel.push_back(rel_i);
    }
    game->ReltoRank();
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
                double rand = random01();
                bool R = (rand <= 0.5);
                if (R) {
                    rel[i][j] = false;
                    rel[j][i] = true;
                }
            }
        ranking[i] = A[i] = i;
    }
    game->ReltoRank();
}