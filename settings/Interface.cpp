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
    shuffle(permutation.begin(), permutation.end(), std::default_random_engine(seed));

    return permutation;
}

void SortGame::init() {
    A.resize(0);
    preds.resize(0);
    ranking.resize(0);
}

SortGame::SortGame() {
    SortGame(10);
}
SortGame::SortGame(int size) {
    for (int i = 0; i < size; i++) {
        A.push_back(i);
        ranking.push_back(i);
        preds.push_back(size - i - 1);
    }
}

int SortGame::getSize() const {
    return A.size();
}

bool SortGame::compare(int i, int j) {
    cmp_counter++;
    // if (A[i] == A[j]) {
    //     cerr << i << " " << j << " " << "equal, fucked up" << endl;
    //     exit(1);
    // }
    // if ((A[i] < A[j]) != (ranking[i] < ranking[j])) {
    //     cerr << "inconsistancy " << i << " " << j << " " << A[i] << " " << A[j] << " " << ranking[i] << " " << ranking[j] << endl;
    //     exit(1);
    // }
    // cerr << "comparing " << A[i] << " and " << A[j] << endl;
    return ranking[i] < ranking[j];
}

bool SortGame::isSameAsRank(const std::vector<int>& input) const {
    return input == ranking;
}

const std::vector<int>& SortGame::getPreds() const {
    return preds;
}

double SortGame::eta_diff() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        sum += std::log2(std::abs(preds[i] - ranking[i]) + 1);
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
        sum += std::log2(count);
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
        sum += std::log2(count);
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
        sum += std::min(std::log2(count1), std::log2(count2));
    }
    return sum;
}

void SortGame::summary() {
    cerr << "eta_diff = " << eta_diff() << endl;
    cerr << "eta_left = " << eta_left() << endl;
    cerr << "eta_right = " << eta_right() << endl;
    cerr << "eta_min = " << eta_min() << endl;
}

void SortGame::output_rank()
{
    for (int i = 0; i < getSize(); ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void SortGame::print() {
    cerr << "index, rank, pred" << endl;
    for (int i = 0; i < getSize(); ++i) {
        cerr << i << ": " << A[i] << ", " << ranking[i] << ", " << preds[i] << endl;
    }
}

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