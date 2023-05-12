#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool OESM::if_sorted(SortGame &game, int st, int ed) {
    for (int i = st + 1; i < ed; i++)
        if (game.compare(indexes[i], indexes[i - 1])) {
            // cerr << "checking sortedness of " << st << " " << ed << " fail at " << i << ", " << indexes[i] << " " << indexes[i - 1] << endl;
            return false;
        }
    return true;
}

void OESM::sort(SortGame &game)
{
    int n = game.getSize();
    new_pred();

    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;
    
    OESM_recursion(game, 0, n);

    index_to_rank();
}

void OESM::merge (SortGame &game, int st, int mid, int ed) {
    //merge two sorted list at indexes[st:mid] and indexes[mid:ed]
    // cerr << "before merge" << endl;
    // for (int i = st; i < ed; i++)
    //     cerr << indexes[i] << " ";
    // cerr << endl;
    merged.clear();
    int i = st, j = mid;
    while (i < mid && j < ed) {
        if (game.compare(indexes[i], indexes[j]))
            merged.push_back(indexes[i++]);
        else
            merged.push_back(indexes[j++]);
    }
    while (i < mid) merged.push_back(indexes[i++]);
    while (j < ed)  merged.push_back(indexes[j++]);
    for (int i = 0; i < merged.size(); i++)
        indexes[st + i] = merged[i];    
    // cerr << "after merge" << endl;
    // for (int i = st; i < ed; i++)
    //     cerr << indexes[i] << " ";
    // cerr << endl;
}

void OESM::OESM_recursion (SortGame &game, int st, int ed) {
    // cerr << "OESM_recursion " << st  << " " << ed << endl;
    if (st + 1 >= ed) {
        // cerr << "too small" << endl;
        return;
    }
    if (if_sorted(game, st, ed)) {
        // cerr << "sorted" << endl;
        return;
    }
    int mid = (st + ed) / 2;
    // cerr << "merge mid " << st << " " << mid << " " << ed << endl;
    // cerr << "init arrays" << endl;
    // for (int i = st; i < ed; i++)
    //     cerr << indexes[i] << " ";
    // cerr << endl;

        // add to odd_l, even_l, odd_r, even_r
        odd_l.clear();
    even_l.clear();
    odd_r.clear();
    even_r.clear();
    for (int i = st; i < ed; i++) {
        if (i % 2 == 0) {
            if (i < mid)    odd_l.push_back(indexes[i]);
            else            odd_r.push_back(indexes[i]);
        }
        else {
            if (i < mid)    even_l.push_back(indexes[i]);
            else            even_r.push_back(indexes[i]);
        }
    }
    // cerr << "check size " << st << " " << ed << " " << odd_l.size() << " " << even_l.size() << " " << odd_r.size() << " " << even_r.size() << endl;
    //put them back to indexes
    for (int i = 0; i < odd_l.size(); i++)  indexes[st + i] = odd_l[i];
    for (int i = 0; i < even_l.size(); i++) indexes[st + odd_l.size() + i] = even_l[i];
    for (int i = 0; i < odd_r.size(); i++)  indexes[mid + i] = odd_r[i];
    for (int i = 0; i < even_r.size(); i++) indexes[mid + odd_r.size() + i] = even_r[i];
    // cerr << "four segments: " << st << " " << st + odd_l.size() << " " << st +mid << " " << mid + odd_r.size() << " " << ed << endl;

    //divide and conquer
    int lmid = st + odd_l.size();
    int rmid = mid + odd_r.size();
    OESM_recursion(game, st, lmid); //odd_l
    OESM_recursion(game, lmid, mid); //even_l
    OESM_recursion(game, mid, rmid); //odd_r
    OESM_recursion(game, rmid, ed); //even_r

    
    // cerr << "sorted 4 arrays: " << endl;
    // for (int i = st; i < ed; i++)  cerr << indexes[i] << " ";
    // cerr << endl;

    //merge
    

    merge (game, st, lmid, mid);
    merge (game, mid, rmid, ed);
    merge (game, st, mid, ed);
}

