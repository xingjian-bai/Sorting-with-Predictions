#pragma once
#include <vector>
#include <iostream>
using namespace std;
class SortGame {
public:
    SortGame(); 
    SortGame(int size); // 构造函数，随机生成A、preds，并计算rank

    bool compare(int i, int j);

    bool isSameAsRank(const std::vector<int>& input) const;
    const std::vector<int>& getPreds() const;
    int getSize() const;

    // sum of log of (p_i - t_i)
    double eta_diff() const;
    // sum of log of (number of j with A_j > A_i but p_j < p_i)
    double eta_left() const;
    // sum of log of (number of j with A_j < A_i but p_j > p_i)
    double eta_right() const;
    double eta_min() const;

    int counter() const { return cmp_counter; }

    void print() {
        cerr << "index, rank, pred" << endl;
        for (int i = 0; i < getSize(); ++i) {
            cerr << "A_" << i << "=" << rank[i] << ",p=" << preds[i] << endl;
        }
    }
    double summary() {
        // cerr << "eta_diff = " << eta_diff() << endl;
        // cerr << "eta_left = " << eta_left() << endl;
        // cerr << "eta_right = " << eta_right() << endl;
        // cerr << "cost = " << counter() << endl;
        // cerr << "RATIO:" << counter() / eta_diff() << endl;
        return counter() / eta_min();
    }
private:
    std::vector<int> A;         // 数字数组
    std::vector<int> preds;     // 预测排名数组
    std::vector<int> rank;      // 真实排名数组
    int cmp_counter = 0;        // 比较计数器

    void calculateRank();       // 计算rank数组
};
