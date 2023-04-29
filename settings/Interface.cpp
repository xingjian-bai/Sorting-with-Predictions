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

SortGame::SortGame() {
    SortGame(10);
}
SortGame::SortGame(int size) {
    // 初始化随机数生成器
    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<> dist(1, 100);

    // 生成大小为size的A和preds排列
    A = generateRandomPermutation(size);
    preds = generateRandomPermutation(size);
    // 计算rank数组
    rank = A;
}

int SortGame::getSize() const {
    return static_cast<int>(A.size());
}

bool SortGame::compare(int i, int j) {
    cmp_counter++;
    // cerr << "comparing " << A[i] << " and " << A[j] << endl;
    return A[i] < A[j];
}

bool SortGame::isSameAsRank(const std::vector<int>& input) const {
    return input == rank;
}

const std::vector<int>& SortGame::getPreds() const {
    return preds;
}

double SortGame::eta_diff() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        sum += std::log2(std::abs(preds[i] - rank[i]) + 1);
    }
    return sum;
}

double SortGame::eta_left() const {
    double sum = 0;
    for (int i = 0; i < getSize(); ++i) {
        int count = 0;
        for (int j = 0; j < getSize(); ++j) {
            if (A[j] > A[i] && preds[j] < preds[i]) {
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
            if (A[j] < A[i] && preds[j] > preds[i]) {
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
            if (A[j] > A[i] && preds[j] < preds[i]) {
                count1++;
            }
            if (A[j] < A[i] && preds[j] > preds[i]) {
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
        cout << rank[i] << " ";
    }
    cout << endl;
}

void SortGame::print() {
    cerr << "index, rank, pred" << endl;
    for (int i = 0; i < getSize(); ++i) {
        cerr << "A_" << i << "=" << rank[i] << ",p=" << preds[i] << endl;
    }
}