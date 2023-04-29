#include "LIS.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



std::vector<int> LIS::sort(SortGame &game)
{
    int n = game.getSize();
    vector<int> preds = game.getPreds();
    vector<int> uni_preds = new_pred(preds); // 重排preds，使得preds中的数字连续
    // vector<int> uni_preds = preds;
    int p_to_A[n];
    for (int i = 0; i < n; i++)
        p_to_A[uni_preds[i]] = i;

    vector<int> sorted;
    int finger = -1;
    for (int index = 0; index < n; index ++) {
        int i_in_A = p_to_A[index];
        // cerr << "sorted at index = " << index << endl;
        // for (int i = 0; i < sorted.size(); i++)
        //     cerr << sorted[i] << " ";
        // cerr << endl;
        
        
        // if (finger != -1)
        //     cerr << "finger = " << finger << " i is small?" << game.compare(i_in_A, sorted[finger]) << endl;
        if (finger == -1) {
            sorted.push_back(i_in_A);
            finger = 0;
        } 
        else if (game.compare(i_in_A, sorted[finger])) { // a[i] < a[sorted[finger]]
            int gap = 1;
            while (finger - gap >= 0 && game.compare(i_in_A, sorted[finger - gap])) {
                // cerr << "i is smaller than index " << finger - gap << endl;
                gap <<= 1;
            }
            int st = max(0, finger - gap);
            if (st == 0) {
                // cerr << "case 1" << endl;
                if (game.compare(i_in_A, sorted[0]))
                {
                    sorted.insert(sorted.begin(), i_in_A);
                    finger = 0;
                    continue;
                }
            }
            // int ed = finger - (gap >> 1);
            int ed = finger;
            while (ed - st > 1)
            {
                int mid = (st + ed) >> 1;
                if (game.compare(i_in_A, sorted[mid]))   ed = mid;
                else                                st = mid;
            }
            // cerr << "case 2 " << max(0, finger - gap + 1) << " " << finger << " > " << ed << endl;

            sorted.insert(sorted.begin() + ed, i_in_A);
            finger = ed;
        }
        else { //a[i] > a[sorted[finger]]
            int gap = 1;
            while (finger + gap < sorted.size() && game.compare(sorted[finger + gap], i_in_A))
                gap <<= 1;
            int ed = min((int)sorted.size() - 1, finger + gap);
            if (ed == sorted.size() - 1) {
                if (game.compare(sorted[sorted.size() - 1], i_in_A)) {
                    // cerr << "case 3 " << sorted.size() - 1 << endl;
                    sorted.push_back(i_in_A);
                    finger = sorted.size() - 1;
                    continue;
                }
            }
            // int st = finger + (gap >> 1);
            int st = finger;
            while (ed - st > 1)
            {
                int mid = (st + ed) >> 1;
                if (game.compare(sorted[mid], i_in_A))   st = mid;
                else                                ed = mid;
            }
            sorted.insert(sorted.begin() + ed, i_in_A);
            // cerr << "case 4 " << finger << " " << min((int)sorted.size() - 1, finger + gap) << " > " << ed << endl;
            finger = ed;
        }
        
    }
    // cerr << "final" << endl;
    // for (int i = 0; i < sorted.size(); i++)
    //     cerr << sorted[i] << " ";
    // cerr << endl;
    return index_to_rank(sorted);
}

