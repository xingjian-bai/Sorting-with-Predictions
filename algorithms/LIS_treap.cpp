#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



void LIS_treap::sort(SortGame &game)
{
    indexes.clear();
    output_rank.clear();
    int n = game.getSize();
    new_pred();

    p_to_A.resize(n);
    for (int i = 0; i < n; i++)
        p_to_A[uni_preds[i]] = i;

    Treap treap;
    Node *finger = nullptr;

    Comp dirty = [&](int a, int b) {
        bool result = game.compare(a, b);
        return result;
    };
    Comp clean = [&](int a, int b) {
        // cerr << "clean compare " << a << " " << b << endl;
        bool result = game.compare(a, b);
        return result;
    };

    for (int index = 0; index < n; index ++) {
        ll prev_cmp = game.counter();
        int ai = p_to_A[index];
        // cerr << "inserting index: " << index << " ai: " << ai << endl;

        if (finger == nullptr) {
            // cerr << "boom! " << endl;
            finger = treap.root = new Node(ai);
            continue;
        }
        // cerr << "init finger value" << finger->value << endl;

        bool leftInclude = (finger->st == -inf) || game.compare(finger->st, ai);
        bool rightInclude = (finger->ed == inf) || game.compare(ai, finger->ed);

        // cerr << "mid finger value" << finger->value << endl;


        while (!leftInclude || !rightInclude)
        {
            
            // cerr << "check finger: " << finger->value << " " << finger->st << " " << finger->ed << " " << ai << " " << leftInclude << " " << rightInclude << endl;
            finger = finger->parent;
            if (finger == nullptr)
            {
                // cerr << "finger is null, done" << endl;
                assert(false);
            }

            leftInclude |= (finger->st == -inf) || game.compare(finger->st, ai);
            rightInclude |= (finger->ed == inf) || game.compare(ai, finger->ed);
        }
        // cerr << "reach finger value/st/ed" << finger->value << " " << finger->st << " " << finger->ed << endl;

        Comp dirty = [&](int a, int b)
        {
            if (a == finger->value || b == finger->value)
                return !clean(a, b);
            if (a == ai)
            {
                if (b <= finger->st)
                    return false;
                if (b >= finger->ed)
                    return true;
            }
            if (b == ai)
            {
                if (a <= finger->st)
                    return true;
                if (a >= finger->ed)
                    return false;
            }
            cerr << "querying dirty compare " << a << " " << b << " which should not happen" << endl;
            assert(false);
            return false;
        };
        finger = treap.insert(ai, dirty, clean, finger->value);
        // cerr << "after insert " << ai << ", now have finger " << finger->value << " with st and ed " << finger->st << " " << finger->ed << endl;
        // treap.LinearPrint(treap.root);
    }
    // cerr << "final" << endl;
    // for (int i = 0; i < sorted.size(); i++)
    //     cerr << sorted[i] << " ";
    // cerr << endl;
    
    treap.LinearOutput(&indexes);
    index_to_rank();
}

