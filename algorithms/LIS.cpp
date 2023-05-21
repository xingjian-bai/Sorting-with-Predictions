#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



void LIS::sort(SortGame &game)
{
    indexes.clear();
    output_rank.clear();
    int n = game.getSize();
    new_pred();

    p_to_A.resize(n);
    for (int i = 0; i < n; i++)
        p_to_A[uni_preds[i]] = i;

    ScapegoatTree scapegoat;
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
        // if (index % 10000 == 0)
        //     cerr << "LIS " << index << endl;
        int ai = p_to_A[index];
        // cerr << "inserting " << ai << " with rank, pred = " << ranking[ai] << " " << uni_preds[ai] << endl;

        if (finger == nullptr) {
            finger = scapegoat.root = new Node(ai);
            continue;
        }

        bool leftInclude = (finger->st == -inf) || game.compare(finger->st, ai);
        bool rightInclude = (finger->ed == inf) || game.compare(ai, finger->ed);


        while (!leftInclude || !rightInclude)
        {
            finger = finger->parent;
            if (finger == nullptr)
                assert(false);
            if (!leftInclude)
                leftInclude = (finger->st == -inf) || game.compare(finger->st, ai);
            if (!rightInclude)
                rightInclude = (finger->ed == inf) || game.compare(ai, finger->ed);
        }

        Comp dirty = [&](int a, int b)
        {
            // cerr << "dirty compare " << a << " " << b << endl;
            if (a == finger->value || b == finger->value)
                return !clean(a, b);
            if (a == ai)
            {
                // cerr << b << " " << finger->st << " " << finger->ed << endl;
                if (b <= finger->st)
                    return false;
                if (b >= finger->ed)
                    return true;
            }
            if (b == ai)
            {
                // cerr << a << " " << finger->st << " " << finger->ed << endl;
                if (a <= finger->st)
                    return true;
                if (a >= finger->ed)
                    return false;
            }
            cerr << "querying dirty compare " << a << " " << b << " which should not happen" << endl;
            assert(false);
            return false;
        };
        finger = scapegoat.insert(ai, dirty, clean, finger->value);
    }
    scapegoat.LinearOutput(&indexes);
    index_to_rank();
};

