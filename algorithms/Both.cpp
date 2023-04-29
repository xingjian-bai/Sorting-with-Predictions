#include "Both.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


std::vector<int> BothAlgo::sort(SortGame &game)
{
    // cerr << "BothAlgo::sort" << endl;
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    preds = new_pred(preds); // 重排preds，使得preds中的数字连续

    int p_to_A[n], inserted[n];
    for (int i = 0; i < n; i++) {
        p_to_A[preds[i]] = i;
        inserted[i] = 0;
    }

    vector<int> left, right;
    // cerr counter
    // cerr << "init counter = " << game.counter() << endl;
    for (int delta = 1; delta / 2 <= n; delta <<= 1) {
        for (int i = 0; i < n; i++)
        {
            if (inserted[i])    continue;
            int A_i = p_to_A[i];

            vector <int> left_bef, left_aft;
            for (int j = 0; j < left.size(); j++)
            {
                if (left[j] < i)    left_bef.push_back(left[j]);
                else                left_aft.push_back(left[j]);
            }
            if (left_bef.size() < delta || game.compare(p_to_A[left_bef[left_bef.size() - delta]], A_i))
            {
                inserted[i] = 1;
                if (left_bef.size() < delta && (left_bef.empty() || game.compare(A_i, p_to_A[left_bef[0]]))) {
                    left.insert(left.begin(), i);
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
                for (int j = 0; j < left.size(); j++)
                {
                    if (left[j] == left_bef[st])
                    {
                        left.insert(left.begin() + j + 1, i);
                        break;
                    }
                }
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            if (inserted[i])    continue;
            int A_i = p_to_A[i];

            vector <int> right_bef, right_aft;
            for (int j = 0; j < right.size(); j++)
            {
                if (right[j] < i)    right_bef.push_back(right[j]);
                else                 right_aft.push_back(right[j]);
            }
            if (right_aft.size() < delta || game.compare(A_i, p_to_A[right_aft[delta - 1]]))
            {
                if (right_aft.size() < delta && (right_aft.empty() || game.compare(p_to_A[right_aft[right_aft.size() - 1]], A_i))) {
                    right.push_back(i);
                    // cerr << "case 1" << endl;
                    // for (int i = 0; i < right.size(); i++)    cout << right[i] << " ";cout << endl;
                    inserted[i] = 1;
                    continue;
                }
                // cerr << "case 2" << endl;
                int st = delta / 2;
                int ed = min((int)right_aft.size(), delta);
                while (ed - st > 1)
                {
                    int mid = ((st + ed + 1) >> 1) - 1;
                    if (game.compare(A_i, p_to_A[right_aft[mid]]))   ed = mid + 1;
                    else                                             st = mid + 1;
                }
                for (int j = 0; j < right.size(); j++)
                {
                    if (right[j] == right_aft[st])
                    {
                        right.insert(right.begin() + j, i);
                        inserted[i] = 1;
                        // for (int i = 0; i < right.size(); i++)    cout << right[i] << " ";cout << endl;
                        break;
                    }
                }
            }
        }
        // cerr << "delta " << delta << " " << game.counter() << endl;
    }
    // cout << "combining" << endl;
    // for (int i = 0; i < left.size(); i++)
    //     cout << left[i] << " ";
    // cout << endl;
    // for (int i = 0; i < right.size(); i++)    cout << right[i] << " ";cout << endl;
    

    vector<int> combine;

    while (!left.empty() || !right.empty())
    {
        if (left.empty()) {
            combine.push_back(right.back());
            right.pop_back();
        }
        else if (right.empty()) {
            combine.push_back(left.back());
            left.pop_back();
        }
        else {
            // cerr << "competing " << left.back() << " " << right.back() << endl;
            if (game.compare(p_to_A[left.back()], p_to_A[right.back()])) {
                combine.push_back(right.back());
                right.pop_back();
            }
            else {
                combine.push_back(left.back());
                left.pop_back();
            }
        }
        // for (int i = 0; i < combine.size(); i++)    cout << combine[i] << " ";cout << endl;
    }

    

    //reverse
    combine = vector<int>(combine.rbegin(), combine.rend());

    // for (int i = 0; i < combine.size(); i++)    cout << combine[i] << " ";cout << endl;

    vector <int> rank(n);
    
    for (int i = 0; i < n; i++)
        rank[p_to_A[combine[i]]] = i;

    return rank;
}
