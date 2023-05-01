#pragma once
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

extern std::vector<ll> A;         // 数字数组
extern std::vector<int> preds;     // 预测排名数组
extern std::vector<int> ranking;      // 真实排名数组

class SortGame {
public:
    SortGame(); 
    SortGame(int size); // 构造函数，随机生成A、preds，并计算rank

    bool compare(int i, int j);

    bool isSameAsRank(const std::vector<int>& input) const;
    const std::vector<int>& getPreds() const;
    int getSize() const;

    double eta_diff() const;
    double eta_left() const;
    double eta_right() const;
    double eta_min() const;

    int counter() const { return cmp_counter; }
    void clear_counter() { cmp_counter = 0; }

    void print();
    void summary();
    void output_rank();
    void init();
    
    int cmp_counter = 0;        // 比较计数器
    void calculateRank();       // 计算rank数组
};
