#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



void LIS_small::sort(SortGame &game)
{
    // cerr << "fuck fuck " << endl;
    // exit(0);
    indexes.clear();
    output_rank.clear();

    int n = game.getSize();
    new_pred();

    p_to_A.resize(n);
    for (int i = 0; i < n; i++)
        p_to_A[uni_preds[i]] = i;

    
    int finger = -1;
    for (int index = 0; index < n; index ++) {
        int i_in_A = p_to_A[index];
        if (finger == -1) {
            indexes.push_back(i_in_A);
            finger = 0;
        } 
        else if (game.compare(i_in_A, indexes[finger])) { // a[i] < a[sorted[finger]]
            int gap = 1;
            while (finger - gap >= 0 && game.compare(i_in_A, indexes[finger - gap])) {
                // cerr << "i is smaller than index " << finger - gap << endl;
                gap <<= 1;
            }
            int st = max(0, finger - gap);
            if (st == 0) {
                // cerr << "case 1" << endl;
                if (game.compare(i_in_A, indexes[0]))
                {
                    indexes.insert(indexes.begin(), i_in_A);
                    finger = 0;
                    continue;
                }
            }
            // int ed = finger - (gap >> 1);
            int ed = finger;
            while (ed - st > 1)
            {
                int mid = (st + ed) >> 1;
                if (game.compare(i_in_A, indexes[mid]))   ed = mid;
                else                                st = mid;
            }
            // cerr << "case 2 " << max(0, finger - gap + 1) << " " << finger << " > " << ed << endl;

            indexes.insert(indexes.begin() + ed, i_in_A);
            finger = ed;
        }
        else { //a[i] > a[sorted[finger]]
            //special case if finger = sorted.size() - 1
            if (finger == indexes.size() - 1) {
                indexes.push_back(i_in_A);
                finger = indexes.size() - 1;
                continue;
            }
            int gap = 1;
            while (finger + gap < indexes.size() && game.compare(indexes[finger + gap], i_in_A))
                gap <<= 1;
            int ed = min((int)indexes.size() - 1, finger + gap);
            if (ed == indexes.size() - 1) {
                if (game.compare(indexes[indexes.size() - 1], i_in_A)) {
                    // cerr << "case 3 " << sorted.size() - 1 << endl;
                    indexes.push_back(i_in_A);
                    finger = indexes.size() - 1;
                    continue;
                }
            }
            // int st = finger + (gap >> 1);
            int st = finger;
            while (ed - st > 1)
            {
                int mid = (st + ed) >> 1;
                if (game.compare(indexes[mid], i_in_A))   st = mid;
                else                                ed = mid;
            }
            indexes.insert(indexes.begin() + ed, i_in_A);
            // cerr << "case 4 " << finger << " " << min((int)sorted.size() - 1, finger + gap) << " > " << ed << endl;
            finger = ed;
        }
        
    }
    return index_to_rank();
}
