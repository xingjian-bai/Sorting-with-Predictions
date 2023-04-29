#include "Utils.h"
using namespace std;
vector<int> new_pred(std::vector<int> preds) {
    int n = preds.size();
    std::vector<int> buckets[n + 1];
    std::vector<int> uni_preds = preds;
    
    for (int i = 0; i < n; i++)
        buckets[preds[i]].push_back(i);

    int counter = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            uni_preds[buckets[i][j]] = counter++;
    
    return uni_preds;
}

vector <int> index_to_rank(vector <int> indexes) {
    vector<int> rank(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        rank[indexes[i]] = i;
    }
    return rank;
}