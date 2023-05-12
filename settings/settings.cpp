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
    game->RanktoRel();
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
    game->RanktoRel();
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
    game->RanktoRel();
}



void defaultobject(SortGame *game, int size) {
    // mt19937 gen(static_cast<unsigned>(time(nullptr)));
    game->init();

    vector<int> root[size];
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
    for (int i = 0; i < rowOld.size(); i++)         indexedRowOld.push_back(make_pair(rowOld[i], i));
    sort(indexedRowOld.begin(), indexedRowOld.end());
    preds.resize(rowOld.size());
    for (int i = 0; i < indexedRowOld.size(); i++)  preds[indexedRowOld[i].second] = i;

    vector<pair<ll, int>> indexedRowA;
    for (int i = 0; i < row2021.size(); i++)         indexedRowA.push_back(make_pair(A[i], i));
    sort(indexedRowA.begin(), indexedRowA.end());
    ranking.resize(A.size());
    for (int i = 0; i < indexedRowA.size(); i++)  ranking[indexedRowA[i].second] = A[indexedRowA[i].second] = i;

    game->RanktoRel();
}

void localshuffleobject(SortGame *game, int size, int seg) {
    defaultobject(game, size);

    segs.resize(0);
    for (int i = 0; i < seg; i ++)
        segs.push_back(rand() % size);
    sort(segs.begin(), segs.end());

    for (int i = 0; i <= segs.size(); i++) {
        int st = (i ? segs[i - 1] : 0);
        int ed = (i == segs.size() ? size : segs[i]);

        for (int j = st; j < ed; j++) {
            preds[j] = st + rand() % (ed - st);
        }
    }

    game->RanktoRel();
}



void decayobject(SortGame *game, int size, double decay) {
    defaultobject(game, size);

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
        }
    
    game->RanktoRel();
}

void decayobject2(SortGame *game, int size, double decay) {
    defaultobject(game, size);

    // double ratio = log(size) / size;
    // cerr << "error ratio: " << ratio << endl;
    // cerr << "rand01: " << random01() << endl;
    // for (int dec = 0; dec < decay * size; dec ++)
    mt19937 generator;
    int stddev = sqrt(decay * size);
    cerr << "stddev: " << stddev << endl;
    for (int i = 0; i < size; i++) {
        // generate a normal distribution around i
        //define gen
        int mean = preds[i];
        if (random01() > 1.0 / sqrt(size * decay))
            continue ;        
        
        normal_distribution<double> distribution(mean, stddev);
        int newpred = distribution(generator);
        // cerr << "stddev=" << stddev << ", new gen " << newpred << " from " << preds[i] << endl;
        preds[i] = min(max(newpred, 0), size - 1);
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

void inverserelation(SortGame *game, int size) {
    game->init();

    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
    }
    for (int i = 0; i < size; i++) {
        vector <bool> rel_i(size, false);
        for (int j = 0; j < i; j ++)
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

void Productrelation(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);

    double coef[size];
    
    for (int i = 0; i < A.size(); i++)
        coef[i] = random01() * sqrt(ratio);
    
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (random01() < coef[i] * coef[j]) {
                bool R = (random01() <= 0.5);
                rel[i][j] = R;
                rel[j][i] = !R;
            }
    game->ReltoRank();
}

void Productrelation2(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);

    int ifSub[size];
    int classes = ratio * size;

    for (int i = 0; i < A.size(); i++)
        ifSub[i] = (ll) rand() * rand() % classes;
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (ifSub[i] != ifSub[j]) {
                bool R = (random01() <= 0.5);
                rel[i][j] = R;
                rel[j][i] = !R;
            }
}

void IndepRelation(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);
    
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (random01() < ratio) {
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
                bool R = (random01() <= 0.3);
                if (R) {
                    rel[i][j] = false;
                    rel[j][i] = true;
                }
                // rel[i][j] = false;
                // rel[j][i] = true;
            }
        ranking[i] = A[i] = i;
    }
    game->ReltoRank();
}

void Tennisrelation(SortGame *game, int size) {
    game->init();
    const string filename = "data/tennis_relation.txt";

    vector<vector<bool>> tennis_rel = parseTennisRelation(filename, size);    
    // cerr << "tennis relation size: " << tennis_rel.size() << endl;
    
    //cerr tennis_rel
    // for (int i = 0; i < tennis_rel.size(); i++) {
        // cerr << "size: " << tennis_rel[i].size() << endl;
        // for (int j = 0; j < tennis_rel[i].size(); j++)
            // cerr << tennis_rel[i][j] << " ";
        // cerr << endl;
    // }

    size = tennis_rel.size();
    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
    }
    rel = tennis_rel;
    game->ReltoRank();
}

double sigmoid (double x, double lambda) {
    return 1.0 / (1.0 + exp(-lambda * x * x));
}
void SigmoidRelation(SortGame *game, int size, double ratio) {
    defaultrelation(game, size);

    
    for (int i = 0; i < A.size(); i++) {
        for (int j = i + 1; j < A.size(); j++) {
            double x = (j - i) / (double) size;
            double p = sigmoid(x, ratio);
            if (random01() > p) {
                rel[i][j] = 0;
                rel[j][i] = 1;
            }
        }
    
    }
    game->ReltoRank();
}