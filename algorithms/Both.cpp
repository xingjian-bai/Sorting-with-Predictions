#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


void BothAlgo::sort(SortGame &game)
{
    int n = game.getSize();
    new_pred();
    inserted.resize(n);
    p_to_A.resize(n);
    for (int i = 0; i < n; i++) {
        p_to_A[uni_preds[i]] = i;
        inserted[i] = 0;
    }


    ScapegoatTree left_sorted_tree, right_sorted_tree;
    ai_to_node.clear(); ai_to_node.resize(n);

    int inserted_count = 0;
    for (int delta = 1; delta / 2 <= n && inserted_count < n; delta <<= 1)
    {
        ScapegoatTree left_bef, right_aft;

        Comp left_sorted_cmp = [&](int a, int b){return left_sorted_tree.compare(ai_to_node[a], ai_to_node[b]);};
        Comp right_sorted_cmp = [&](int a, int b){return right_sorted_tree.compare(ai_to_node[a], ai_to_node[b]);};

        for (int i = 0; i < n; i++)
        {
            int A_i = p_to_A[i];
            if (inserted[A_i] != 0) {
                if (inserted[A_i] > 0)
                    left_bef.insert(A_i, left_sorted_cmp, left_sorted_cmp, -1);
                continue;
            }
            Node *lowerbound = left_bef.find_kth_largest(left_bef.root, delta);

            if (lowerbound == nullptr || game.compare(lowerbound->value, A_i)) {
                Node *target;
                if (lowerbound == nullptr) {
                    Comp left_bef_comp = [&](int a, int b){return game.compare(a, b);};
                    target = left_bef.find_largest_small(left_bef.root, A_i, left_bef_comp);
                }
                else if (delta == 1)
                    target = lowerbound;
                else {
                    Comp left_bef_comp = [&](int a, int b){
                        assert(b == A_i);
                        if (left_sorted_tree.compare(ai_to_node[a], ai_to_node[lowerbound->value]))
                            return true;
                        return game.compare(a, A_i);
                    };
                    target = left_bef.find_largest_small(left_bef.root, A_i, left_bef_comp);
                }
                Comp left_dirty = [&](int a, int b)
                {
                    assert (a == A_i);
                    if (target == nullptr || b == target->value)    return true;
                    return left_sorted_tree.compare(ai_to_node[target->value], ai_to_node[b]);
                };
                Comp left_clean = [&](int a, int b){return true;};

                ai_to_node[A_i] = left_sorted_tree.insert(A_i, left_dirty, left_clean, target == nullptr ? -1 : target->value);
                inserted[A_i] = delta;
                left_bef.insert(A_i, left_sorted_cmp, left_sorted_cmp, -1);
                inserted_count++;
            }
        }

        for (int i = n - 1; i >= 0; i --)
        {
            int A_i = p_to_A[i];
            if (inserted[A_i] != 0) {
                if (inserted[A_i] < 0)
                    right_aft.insert(A_i, right_sorted_cmp, right_sorted_cmp, -1);
                continue;
            }
            Node *upperbound = right_aft.find_kth_smallest(right_aft.root, delta);

            if (upperbound == nullptr || game.compare(A_i, upperbound->value)) {
                Node *target;
                if (upperbound == nullptr) {
                    Comp right_aft_comp = [&](int a, int b){return game.compare(a, b);};
                    target = right_aft.find_smallest_large(right_aft.root, A_i, right_aft_comp);
                }
                else {
                    Comp right_aft_comp = [&](int a, int b){
                        assert(a == A_i);
                        if (right_sorted_tree.compare(ai_to_node[upperbound->value], ai_to_node[b]))
                            return true;
                        return game.compare(A_i, b);
                    };
                    target = right_aft.find_smallest_large(right_aft.root, A_i, right_aft_comp);
                }
                Comp right_dirty = [&](int a, int b)
                {
                    assert (a == A_i);
                    if (target == nullptr)
                        return false;
                    if (b == target->value)
                        return false;
                    return right_sorted_tree.compare(ai_to_node[target->value], ai_to_node[b]);
                };
                Comp right_clean = [&](int a, int b){return false;};

                ai_to_node[A_i] = right_sorted_tree.insert(A_i, right_dirty, right_clean, target == nullptr ? -1 : target->value);
                inserted[A_i] = -delta;
                right_aft.insert(A_i, right_sorted_cmp, right_sorted_cmp, -1);
                inserted_count++;
            }
        }
    }
    // cerr << "left_sorted: " << left_sorted.size() << endl;
    left_sorted.resize(0); left_sorted_tree.LinearOutput(&left_sorted);
    right_sorted.resize(0); right_sorted_tree.LinearOutput(&right_sorted);

    // cerr << "left_sorted and right_sorted: " << endl;
    // for (int i = 0; i < left_sorted.size(); i++)
    //     cerr << left_sorted[i] << " ";
    // cerr << endl;
    // for (int i = 0; i < right_sorted.size(); i++)
    //     cerr << right_sorted[i] << " ";
    // cerr << endl;

    combine.resize(0);

    int lpt = 0, rpt = 0;
    while (lpt < left_sorted.size() || rpt < right_sorted.size()) {
        if (lpt == left_sorted.size())
            combine.push_back(right_sorted[rpt++]);
        else if (rpt == right_sorted.size())
            combine.push_back(left_sorted[lpt++]);
        else if (game.compare(left_sorted[lpt], right_sorted[rpt]))
            combine.push_back(left_sorted[lpt++]);
        else
            combine.push_back(right_sorted[rpt++]);
    }

    output_rank.resize(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        output_rank[combine[i]] = i;
    }
}
