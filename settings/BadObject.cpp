#include "BadObjects.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;


BadObjects::BadObjects(int size, double prob) {
    mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

    // vector<int> root[size];
    // for (int i = 0; i < size; i++) {
    //     root[i] = i;

    // }

    // vector <int> A(size), preds(size), rank(size);
    for (int i = 0; i < size; i++) {
        A.push_back(i);
        rank.push_back(i);
        preds.push_back(size - i - 1);
    }
}