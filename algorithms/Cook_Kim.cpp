#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool Cook_Kim::if_sorted(SortGame &game, int st, int ed) {
    for (int i = st + 1; i < ed; i++)
        if (game.compare(indexes[i], indexes[i - 1]))
            return false;
    return true;
}

void Cook_Kim::sort(SortGame &game)
{
    int n = game.getSize();
    new_pred();

    indexes.resize(n);
    for (int i = 0; i < n; i++)
        indexes[uni_preds[i]] = i;
    
    Cook_Kim_recursion(game, 0, n);

    index_to_rank();
}

void Cook_Kim::merge (SortGame &game, int st, int mid, int ed) {
    //merge two sorted list at indexes[st:mid] and indexes[mid:ed]
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
}

void Cook_Kim::Cook_Kim_recursion (SortGame &game, int st, int ed) {
    if (ed - st <= 1)
        return;
    if (if_sorted(game, st, ed))
        return;
    
    ordered.clear(); unordered1.clear(); 
    // unordered2.clear();
    for (int i = st; i < ed; i++) {
        if (ordered.empty() || game.compare(ordered.back(), indexes[i]))
            ordered.push_back(indexes[i]);
        else {
            int back = ordered.back();
            ordered.pop_back();
            unordered1.push_back(indexes[i]);
            unordered1.push_back(back);
            // unordered2.push_back(indexes[i]);
        }
    }
    for (int i = 0; i < ordered.size(); i++)
        indexes[st + i] = ordered[i];
    for (int i = 0; i < unordered1.size(); i++)
        indexes[st + ordered.size() + i] = unordered1[i];
    // for (int i = 0; i < unordered2.size(); i++)
        // indexes[st + ordered.size() + unordered1.size() + i] = unordered2[i];
    int mid1 = st + ordered.size();
    int mid2 = st + ordered.size() + (ed - st - ordered.size()) / 2;

    Cook_Kim_recursion(game, mid1, mid2);
    Cook_Kim_recursion(game, mid2, ed);

    merge(game, st, mid1, mid2);
    merge(game, st, mid2, ed);
}

