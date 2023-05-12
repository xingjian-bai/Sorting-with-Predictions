#pragma once
#include <vector>
#include <iostream>
// #include "../algorithms/SortAlgo.h"
using namespace std;
typedef long long ll;

extern std::vector<ll> A;         // 数字数组
extern std::vector<int> preds;     // 预测排名数组
extern std::vector<int> ranking;      // 真实排名数组
extern std::vector<vector<bool>> rel; // 关系数组

class SortGame {
public:
    SortGame() {}

    bool compare(int i, int j)      {
        assert(i != j);
        cmp_counter++;
        return ranking[i] < ranking[j];
    }
    bool dirtyCompare(int i, int j) { return rel[i][j];}

    //it takes a pointer to a vector
    bool isSameAsRank(const std::vector<int>& v) const {
        assert(v.size() == A.size());
        for (int i = 0; i < A.size(); ++i) {
            if (ranking[i] != v[i]) return false;
        }
        return true;
    }

    int getSize() const { return A.size(); }

    double eta_diff() const;
    double eta_left() const;
    double eta_right() const;
    double eta_min() const;
    double eta_dirty() const;

    ll counter() const { return cmp_counter; }
    void clear_counter() { cmp_counter = 0; }

    void print() {
        cerr << "i a r p" << endl;
        for (int i = 0; i < getSize(); ++i)
            cerr << i << ": " << A[i] << ", " << ranking[i] << ", " << preds[i] << endl;
        cerr << "rel:" << endl;
        for (int i = 0; i < getSize(); ++i) {
            for (int j = 0; j < getSize(); ++j) {
                cerr << rel[i][j] << " ";
            }
            cerr << endl;
        }
    }
    void output_rank() {for (int i = 0; i < getSize(); ++i) cout << A[i] << " ";cout << endl;}
    void init() { A.resize(0); preds.resize(0); ranking.resize(0);
        rel.resize(0);
        cmp_counter = 0;
    }
    // void summary();
    
    ll cmp_counter = 0;        // 比较计数器
    void calculateRank();       // 计算rank数组

    void ReltoRank();           
    void ReltoRank_recursion(int l, int r); 
    void RanktoRel();          
};
