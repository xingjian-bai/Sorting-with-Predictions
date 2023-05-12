#include "SortAlgo.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <random>
#include <functional>
#include <tuple>
#include <map>

using namespace std;
typedef function<bool(int, int)> Comp;




void DirtyClean2::sort(SortGame &game)
{
    vector <Node*> path;
    map <pair<int, int>, bool> dirty_records, clean_records;
    Treap treap;
    Comp dirty = [&](int a, int b) {
        if (dirty_records.count(make_pair(a, b)))
            return dirty_records[make_pair(a, b)];
        // cerr << "dirty compare " << a << " " << b << endl;
        bool result = game.dirtyCompare(a, b);
        dirty_records[make_pair(a, b)] = result;
        dirty_records[make_pair(b, a)] = !result;
        return result;
    };
    Comp clean = [&](int a, int b) {
        // cerr << "clean compare " << a << " " << b << endl;
        if (clean_records.count(make_pair(a, b)))
            return clean_records[make_pair(a, b)];
        bool result = game.compare(a, b);
        clean_records[make_pair(a, b)] = result;
        clean_records[make_pair(b, a)] = !result;
        return result;
    };


    auto insertElement = [&](int ai) {
        // cerr << "insert " << ai << endl;
        Node* p1 = treap.insert(ai, dirty, clean);
        // cerr << "inserted " << ai << endl;
        Node* p1_copy = p1, * p1_up = p1;

        path.resize(0);
        while (p1_up != nullptr) {
            // cerr << "if null" << (p1_up == nullptr) << endl;
            // cerr << "p1_up: " << p1_up->st << " " << p1_up->ed << endl;
            path.push_back(p1_up);
            p1_up = p1_up->parent;
        }
        // cerr << "path size: " << path.size() << endl;

        bool leftInclude = (p1->st == -inf) || game.compare(p1->st, ai);
        bool rightInclude = (p1->ed == inf) || game.compare(ai, p1->ed);
        // cerr << "leftInclude: " << leftInclude << " rightInclude: " << rightInclude << endl;

        int minLeftInclude = inf, minRightInclude = inf;

        int st = 0, ed = 0;
        // cerr << "path size: " << path.size() << endl;
        while (!leftInclude || !rightInclude)
        {
            st = ed;
            ed = min((int)path.size() - 1, max(ed + 1, ed * 2));
            Node * tg = path[ed];
            if (!leftInclude)
                leftInclude = (tg->st == -inf) || game.compare(tg->st, ai);
            if (!rightInclude)
                rightInclude = (tg->ed == inf) || game.compare(ai, tg->ed);
            if (leftInclude)    minLeftInclude = min(minLeftInclude, ed);
            if (rightInclude)   minRightInclude = min(minRightInclude, ed);
        }
        // cerr << "ed: " << ed << endl;


        
        while (st < ed) {
            int mid = (st + ed) >> 1;
            Node *tg = path[mid];
            bool leftInclude = (tg->st == -inf) || minLeftInclude <= mid;
            bool rightInclude = (tg->ed == inf) || minRightInclude <= mid;
            
            if (!leftInclude) {
                if (game.compare(tg->st, ai)) {
                    leftInclude = true;
                    minLeftInclude = min(minLeftInclude, mid);
                }
            }
            if (!leftInclude) {
                st = mid + 1;
                continue;
            }

            if (!rightInclude)
            {
                if (game.compare(ai, tg->ed)) {
                    rightInclude = true;
                    minRightInclude = min(minRightInclude, mid);
                }
            }
            if (!rightInclude) {
                st = mid + 1;
                continue;
            }

            ed = mid;
        }

        // cerr << "min inclusion: " << ed << endl;
        Node *turn = path[ed];

        if (turn->value == ai)    return;
        
        treap.deleteNode(p1_copy);
        Node* p2 = treap.insert(ai, dirty, clean, turn->value);

        // turn->priority = -inf + rand() % (2 * inf);
        turn->priority = rand() - inf;
        treap.rebalance(turn);
    };

    int n = game.getSize();
    shuffledA.resize(n);
    for (int i = 0; i < n; ++i)
        shuffledA[i] = i;
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffledA.begin(), shuffledA.end(), g);

    for (int ai : shuffledA) {
    // for (int ai = 0; ai < n; ++ai)
        insertElement(ai);
        
        indexes.resize(0);
        treap.LinearOutput(&indexes);
        // cerr << "indexes" << endl;
        //     for (int i = 0; i < indexes.size(); ++i)
        //         cerr << indexes[i] << " ";
        //     cerr << endl;
    }

    indexes.resize(0);
    treap.LinearOutput(&indexes);

    // cerr << "indexes final" << endl;
    // for (int i = 0; i < indexes.size(); ++i)
    //     cerr << indexes[i] << " ";
    // cerr << endl;



    index_to_rank();
}