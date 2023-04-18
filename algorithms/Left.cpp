#include "Left.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

std::vector<int> LeftAlgo::sort(SortGame &game)
{
    // cerr << "LeftAlgo::sort" << endl;
    int n = game.getSize();
    vector<int> preds = game.getPreds();

    int p_to_A[n], inserted[n];
    for (int i = 0; i < n; i++) {
        p_to_A[preds[i]] = i;
        inserted[i] = 0;
    }

    vector<int> left;
    for (int delta = 1; delta / 2 <= n; delta <<= 1) {
        // cerr << "delta = " << delta << endl;
        for (int i = 0; i < n; i++)
        {
            if (inserted[i])    continue;
            // inserting the ith element in p-ranking, with original index A_i
            int A_i = p_to_A[i];
            // cerr << "probing " << i << "th element, with original index " << A_i << endl;

            vector <int> left_bef, left_aft;
            for (int j = 0; j < left.size(); j++)
            {
                if (left[j] < i)    left_bef.push_back(left[j]);
                else                left_aft.push_back(left[j]);
            }
            // cerr << "siguation: " << left_bef.size() << endl;
            if (left_bef.size() < delta || game.compare(p_to_A[left_bef[left_bef.size() - delta]], A_i))
            {
                if (left_bef.size() < delta && (left_bef.empty() || game.compare(A_i, p_to_A[left_bef[0]]))) {
                    // cerr << "case 1" << endl;
                    left.insert(left.begin(), i);
                    inserted[i] = 1;

                    // for (int i = 0; i < left.size(); i++)
                    //     cerr << left[i] << " ";
                    // cerr << endl;


                    continue;
                }
                // cerr << "case 2" << endl;
                int st = max(0, (int)left_bef.size() - delta);
                int ed = left_bef.size();
                // assert that v(left_bef[st]) < v(i)
                // cerr << "launch insert" << st << " " << ed << endl;
                while (ed - st > 1)
                {
                    int mid = (st + ed) >> 1;
                    if (game.compare(p_to_A[left_bef[mid]], A_i))   st = mid;
                    else                                            ed = mid;
                }
                // cerr << "finished binary search " << st << endl;

                //append i to the right of left_bef[st] in the original left array
                for (int j = 0; j < left.size(); j++)
                {
                    if (left[j] == left_bef[st])
                    {
                        // cerr << "find position " << j << endl;
                        left.insert(left.begin() + j + 1, i);
                        inserted[i] = 1;
                        break;
                    }
                }
                // for (int i = 0; i < left.size(); i++)
                //     cerr << left[i] << " ";
                // cerr << endl;

            }
            else
            {
                // delta is not strong enough to insert A_i
                continue;
            }
            
        }
        // cerr << "end of delta = " << delta << endl;
        // for (int i = 0; i < left.size(); i++)
        //     cerr << left[i] << " ";
        // cerr << endl;
    }

    int rank[n];
    for (int i = 0; i < n; i++)
        rank[p_to_A[left[i]]] = i;
    
    return vector<int>(rank, rank + n);
}
