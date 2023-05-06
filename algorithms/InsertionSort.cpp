#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



std::vector<int> InsertionSort::sort(SortGame &game)
{
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    // vector<int> uni_preds = preds;
    int p_to_A[n];
    for (int i = 0; i < n; i++)
        p_to_A[uni_preds[i]] = i;

    vector<int> sorted;
    for (int i = 0; i < n; i++)
    {
        int pos = p_to_A[i];
        int j = sorted.size();
        while (j > 0 && game.compare(pos, sorted[j - 1])) {
            // cerr << "compared " << sorted[j - 1] << " " << pos << endl;
            j--;
        }
        sorted.insert(sorted.begin() + j, pos);

        // cerr << "i = " << i << " pos = " << pos << " j = " << j << endl;
        // for (int j = 0; j < sorted.size(); j++)
        //     cerr << sorted[j] << " ";
        // cerr << endl;
    }

    return index_to_rank(sorted);
}

