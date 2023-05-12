#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


void BothAlgo::sort(SortGame &game)
{
    // cerr << "BothAlgo::sort" << endl;
    int n = game.getSize();
    new_pred();
    // cerr << "n = " << n << endl;

    inserted.resize(n);
    p_to_A.resize(n);

    for (int i = 0; i < n; i++) {
        // cerr << uni_preds.size() << endl;
        // cerr << "i = " << i << " " << uni_preds[i] << endl;
        // cerr << n << " " << p_to_A.size() << endl;
        p_to_A[uni_preds[i]] = i;
        // cerr << "mid" << endl;
        inserted[i] = 0;
        // cerr << "mid2" << endl;
    }

    left_sorted.clear(); right_sorted.clear();
    left_bef.clear();    right_aft.clear();
    // cerr << "n = " << n << endl;
    for (int delta = 1; delta / 2 <= n; delta <<= 1) {
        // cerr << "delta = " << delta << endl;
        for (int i = 0; i < n; i++)
        {
            if (inserted[i])    continue;
            int A_i = p_to_A[i];

            left_bef.resize(0);
            for (int j = 0; j < left_sorted.size(); j++)
                if (left_sorted[j] < i)
                    left_bef.push_back(left_sorted[j]);

            if (left_bef.size() < delta || game.compare(p_to_A[left_bef[left_bef.size() - delta]], A_i))
            {
                inserted[i] = 1;
                if (left_bef.size() < delta && (left_bef.empty() || game.compare(A_i, p_to_A[left_bef[0]]))) {
                    left_sorted.insert(left_sorted.begin(), i);
                    continue;
                }
                int st = max(0, (int)left_bef.size() - delta);
                int ed = left_bef.size() - delta / 2;
                while (ed - st > 1)
                {
                    int mid = (st + ed) >> 1;
                    if (game.compare(p_to_A[left_bef[mid]], A_i))   st = mid;
                    else                                            ed = mid;
                }
                for (int j = 0; j < left_sorted.size(); j++)
                {
                    if (left_sorted[j] == left_bef[st])
                    {
                        left_sorted.insert(left_sorted.begin() + j + 1, i);
                        break;
                    }
                }
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            if (inserted[i])    continue;
            int A_i = p_to_A[i];

            right_aft.resize(0);
            for (int j = 0; j < right_sorted.size(); j++)
                if  (right_sorted[j] > i)
                    right_aft.push_back(right_sorted[j]);
            if (right_aft.size() < delta || game.compare(A_i, p_to_A[right_aft[delta - 1]]))
            {
                if (right_aft.size() < delta && (right_aft.empty() || game.compare(p_to_A[right_aft[right_aft.size() - 1]], A_i))) {
                    right_sorted.push_back(i);
                    inserted[i] = 1;
                    continue;
                }
                int st = delta / 2;
                int ed = min((int)right_aft.size(), delta);
                while (ed - st > 1)
                {
                    int mid = ((st + ed + 1) >> 1) - 1;
                    if (game.compare(A_i, p_to_A[right_aft[mid]]))   ed = mid + 1;
                    else                                             st = mid + 1;
                }
                for (int j = 0; j < right_sorted.size(); j++)
                {
                    if (right_sorted[j] == right_aft[st])
                    {
                        right_sorted.insert(right_sorted.begin() + j, i);
                        inserted[i] = 1;
                        break;
                    }
                }
            }
        }
    }
    // cerr << "left_sorted: " << left_sorted.size() << endl;

    combine.resize(0);
    while (!left_sorted.empty() || !right_sorted.empty())
    {
        if (left_sorted.empty()) {
            combine.push_back(right_sorted.back());
            right_sorted.pop_back();
        }
        else if (right_sorted.empty()) {
            combine.push_back(left_sorted.back());
            left_sorted.pop_back();
        }
        else {
            // cerr << "competing " << left.back() << " " << right.back() << endl;
            if (game.compare(p_to_A[left_sorted.back()], p_to_A[right_sorted.back()])) {
                combine.push_back(right_sorted.back());
                right_sorted.pop_back();
            }
            else {
                combine.push_back(left_sorted.back());
                left_sorted.pop_back();
            }
        }
        // for (int i = 0; i < combine.size(); i++)    cout << combine[i] << " ";cout << endl;
    }
    // cerr << "combine: " << combine.size() << endl;

    

    //reverse combine
    for (int i = 0; i < combine.size() - i - 1; i++)
        swap(combine[i], combine[combine.size() - i - 1]);

    output_rank.resize(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        output_rank[p_to_A[combine[i]]] = i;
    }
}
