#include "Interface.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

vector<int> generateRandomPermutation(int size) {
    vector<int> permutation(size);
    iota(permutation.begin(), permutation.end(), 0);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(permutation.begin(), permutation.end(), default_random_engine(seed));

    return permutation;
}



double SortGame::eta_diff() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        sum += log2(abs(preds[i] - ranking[i]) + 1);
    }
    return sum;
}

double SortGame::eta_left() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        int count = 0;
        for (int j = 0; j < getSize(); ++j) {
            if (ranking[j] > ranking[i] && preds[j] < preds[i]) {
                count++;
            }
        }
        count += 1;
        sum += log2(count);
    }
    return sum;
}


double SortGame::eta_right() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        int count = 0;
        for (int j = 0; j < getSize(); ++j) {
            if (ranking[j] < ranking[i] && preds[j] > preds[i]) {
                count++;
            }
        }
        count += 1;
        sum += log2(count);
    }
    return sum;
}

double SortGame::eta_min() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        int count1 = 0, count2 = 0;
        for (int j = 0; j < getSize(); ++j) {
            if (ranking[j] > ranking[i] && preds[j] < preds[i]) {
                count1++;
            }
            if (ranking[j] < ranking[i] && preds[j] > preds[i]) {
                count2++;
            }
        }
        count1 += 1;
        count2 += 1;
        sum += min(log2(count1), log2(count2));
    }
    return sum;
}

// void SortGame::summary() {
//     cerr << "eta_diff = " << eta_diff() << endl;
//     cerr << "eta_left = " << eta_left() << endl;
//     cerr << "eta_right = " << eta_right() << endl;
//     cerr << "eta_min = " << eta_min() << endl;
// }


void SortGame::calculateRank() {
    ranking.resize(getSize());
    vector<pair<ll, int>> tmp;
    for (int i = 0; i < getSize(); ++i) {
        tmp.push_back(make_pair(A[i], i));
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < getSize(); ++i) {
        ranking[tmp[i].second] = i;
    }
}


double SortGame::eta_dirty() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        for (int j = i + 1; j < getSize(); ++j) {
            if (rel[i][j] != (ranking[i] < ranking[j])) {
                sum += 1;
            }
        }
    }
    return sum;
}

void SortGame::ReltoRank() {
    preds.resize(getSize());
    A.resize(getSize());
    for (int i = 0; i < getSize(); ++i) {
        A[i] = i;
    }
    ReltoRank_recursion(0, getSize());

    for (int i = 0; i < getSize(); ++i)
        preds[A[i]] = i;
    
    // cerr << "ReltoRank finished" << endl;
    // for (int i = 0; i < getSize(); ++i) {
    //     cerr << preds[i] << " ";
    // }
    // cerr << endl;
}
void SortGame::ReltoRank_recursion(int st, int ed) {
    // cerr << "recursion " << st << " " << ed << endl;
    if (st + 1 >= ed) {
        return;
    }
    int pivotIndex = st + rand() % (ed - st);
    int pivot = A[pivotIndex];

    swap(A[st], A[pivotIndex]);
    int i = st + 1, j = ed - 1;
    while (i <= j) {
        while (i <= j && rel[A[i]][pivot]) {
            i++;
        }
        while (i <= j && !rel[A[j]][pivot]) {
            j--;
        }
        if (i <= j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    }  
    swap(A[st], A[j]);
    ReltoRank_recursion(st, j);
    ReltoRank_recursion(j + 1, ed);
}

