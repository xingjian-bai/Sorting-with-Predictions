#include "Interface.h"

class BadObjects : public SortGame {

public:
    BadObjects(); 
    BadObjects(int size, double prob); 

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

private:
    std::vector<int> A;         // 数字数组
    std::vector<int> preds;     // 预测排名数组
    std::vector<int> rank;      // 真实排名数组
    int cmp_counter = 0;        // 比较计数器

    void calculateRank();       // 计算rank数组
};
