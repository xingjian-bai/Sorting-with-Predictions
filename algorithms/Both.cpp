#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


void BothAlgo::sort(SortGame &game)
{
    // cerr << "BothAlgo::sort" << endl;
    int bad_compare = 0;
    int n = game.getSize();
    new_pred();
    // cerr << "n = " << n << endl;
    inserted.resize(n);
    p_to_A.resize(n);
    for (int i = 0; i < n; i++) {
        p_to_A[uni_preds[i]] = i;
        inserted[i] = 0;
    }

    ScapegoatTree left_sorted, right_sorted;

    left_weight.clear(); left_weight.resize(n);
    right_weight.clear(); right_weight.resize(n);
    insert_par.clear(); insert_par.resize(n);

    ai_to_node.clear(); ai_to_node.resize(n);

    for (int delta = 1; delta / 2 <= n; delta <<= 1)
    {
        ScapegoatTree left_bef;
        cerr << "delta = " << delta << endl;

        Comp left_sorted_cmp = [&](int a, int b){
            if (left_weight[a] == left_weight[b]) {
                if (inserted[a] == inserted[b]) {
                    cerr << "terrible comparing " << a << " " << b << endl;
                    bad_compare++;
                    return game.compare(a, b);
                    // int copy_a = a;
                    // cerr << "expected " << game.compare(a, b) << endl;
                    // if (uni_preds[a] > uni_preds[b]) {
                    //     while (a != -1) {
                    //         if (a == b) {
                    //             cerr << false << endl;
                    //             assert (!game.compare(copy_a, b));
                    //             return false;
                    //         }

                    //         a = insert_par[a];
                    //     }
                    //     cerr << true << endl;
                    //     assert (game.compare(copy_a, b));
                    //     return true;
                    // }
                    // else {
                    //     int copy_b = b;
                    //     while (b != -1) {
                    //         if (a == b) {
                    //             cerr << true << endl;
                    //             assert (game.compare(a, copy_b));
                    //             return true;
                    //         }
                    //         b = insert_par[b];
                    //     }
                    //     cerr << false << endl;
                    //     assert (!game.compare(a, copy_b));
                    //     return false;
                    // }
                }
                // assert (game.compare(a, b) == (inserted[a] < inserted[b]));
                return inserted[a] < inserted[b];
            }
            bool result = left_weight[a] < left_weight[b];
            // if (game.compare(a, b) != result) {
            //     cerr << a << " " << b << endl;
            //     cerr << left_weight[a] << " " << left_weight[b] << endl;
            // }
            // assert (game.compare(a, b) == result);
            return result;
        };

        for (int i = 0; i < n; i++)
        {
            int A_i = p_to_A[i];
            if (inserted[A_i] != 0) {
                if (inserted[A_i] > 0)
                    left_bef.insert(A_i, left_prev_cmp, left_prev_cmp, -1);
                continue;
            }
            // cerr << "tempting to insert " << i << " : " << A_i << endl;
            Node *lowerbound = left_bef.find_kth_largest(left_bef.root, delta);
            // cerr << " passed find_kth_largest" << endl;
            if (lowerbound == nullptr || game.compare(lowerbound->value, A_i)) {
                // cerr << "prep inserting " << i << " : " << A_i << endl;
                Node *target;
                // cerr << "lowerbound: " << (lowerbound == nullptr ? -1 : lowerbound->value) << endl;
                if (lowerbound == nullptr) {
                    Comp left_bef_comp = [&](int a, int b)
                    {
                        return game.compare(a, b);
                    };
                    target = left_bef.find_largest_small(left_bef.root, A_i, left_bef_comp);
                }
                else {
                    Comp left_bef_comp = [&](int a, int b)
                    {
                        // a must be in left_bef, and b must be A_i
                        assert(b == A_i);
                        if (left_weight[a] < left_weight[lowerbound->value])
                            return true;
                        return game.compare(a, b);
                    };
                    target = left_bef.find_largest_small(left_bef.root, A_i, left_bef_comp);
                }
                
                //insert A_i into left_sorted, right after target
                Comp left_dirty = [&](int a, int b)
                {
                    // in insert, a must be A_i, and b must be node->value
                    assert (a == A_i);
                    if (target == nullptr)
                        return true;
                    if (b == target->value)
                        return true; //reach target, now goes right and straight left
                    return left_prev_cmp(target->value, b);
                    // return left_weight[target->value] < left_weight[b]; 
                };
                Comp left_clean = [&](int a, int b)
                {
                    // straight left
                    return true;   
                };

                /*
                    If target == nullptr, then insert A_i as the leftmost node
                    Else, insert A_i as the right child of target                
                */
                ai_to_node[A_i] = left_sorted.insert(A_i, left_dirty, left_clean, target == nullptr ? -1 : target->value);
                    

                
                // cerr << " passed left_sorted.insert" << endl;
                inserted[A_i] = delta;
                insert_par[A_i] = (target == nullptr) ? -1 : target->value;
                // cerr << " inserted[" << i << "] = " << inserted[i] << " " << A_i << " " << (target == nullptr) << endl;
                left_weight[A_i] = ((target == nullptr) ? -i : left_weight[target->value]);
                // cerr << "!!!!!!!!! envalue left_weight" << A_i << " to " << left_weight[A_i] << endl;
                // cerr << " left_weight[" << A_i << "] = " << left_weight[A_i] << endl;
                left_bef.insert(A_i, left_prev_cmp, left_prev_cmp, -1);
            
                // cerr << "<<< left_sorted >>>" << endl;
                // left_sorted.LinearPrint(left_sorted.root);
                // cerr << "<<< left_bef >>>" << endl;
                // left_bef.LinearPrint(left_bef.root);
                // cerr << endl;
            }
        }

        left_order.resize(0);
        left_sorted.LinearOutput(&left_order);
        // right_order.resize(0);
        // right_sorted.LinearOutput(&right_order);
        for (int i = 0; i < n; i ++)
            left_weight[i] = 0;
        for (int i = 0; i < left_order.size(); i++)
            left_weight[left_order[i]] = i + 100;
        // for (int i = 0; i < right_order.size(); i++)
            // right_weight[right_order[i]] = i;
    }
    // cerr << "left_sorted: " << left_sorted.size() << endl;

    // combine.resize(0);
    // while (!left_sorted.empty() || !right_sorted.empty())
    // {
    //     if (left_sorted.empty()) {
    //         combine.push_back(right_sorted.back());
    //         right_sorted.pop_back();
    //     }
    //     else if (right_sorted.empty()) {
    //         combine.push_back(left_sorted.back());
    //         left_sorted.pop_back();
    //     }
    //     else {
    //         // cerr << "competing " << left.back() << " " << right.back() << endl;
    //         if (game.compare(p_to_A[left_sorted.back()], p_to_A[right_sorted.back()])) {
    //             combine.push_back(right_sorted.back());
    //             right_sorted.pop_back();
    //         }
    //         else {
    //             combine.push_back(left_sorted.back());
    //             left_sorted.pop_back();
    //         }
    //     }
    //     // for (int i = 0; i < combine.size(); i++)    cout << combine[i] << " ";cout << endl;
    // }
    // // cerr << "combine: " << combine.size() << endl;

    combine.resize(0);
    left_sorted.LinearOutput(&combine);

    //reverse combine
    // for (int i = 0; i < combine.size() - i - 1; i++)
        // swap(combine[i], combine[combine.size() - i - 1]);

    output_rank.resize(indexes.size());
    for (int i = 0; i < indexes.size(); i++) {
        output_rank[combine[i]] = i;
    }
    cerr << "tot=" << game.cmp_counter << endl;
    cerr << "bad=" << bad_compare << endl;
}
