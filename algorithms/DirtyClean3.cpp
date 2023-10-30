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

void DirtyClean3::sort(SortGame &game)
{
    vector <Node*> path;
    map <pair<int, int>, bool> dirty_records, clean_records;
    ScapegoatTree tree;
    Comp dirty = [&](int a, int b)
    {
        pair <int, int> ab = make_pair(a, b);
        pair <int, int> ba = make_pair(b, a);
        if (dirty_records.count(ab))
            return dirty_records[ab];
        bool result = game.dirtyCompare(a, b);
        dirty_records[ab] = result;
        dirty_records[ba] = !result;
        return result;
    };
    Comp clean = [&](int a, int b)
    {
        
        pair<int, int> ab = make_pair(a, b);
        pair<int, int> ba = make_pair(b, a);
        if (clean_records.count(ab))
            return clean_records[ab];
        bool result = game.compare(a, b);
        clean_records[ab] = result;
        clean_records[ba] = !result;
        return result;
    };

    auto find_path = [&](Node* x) {
        Node* helper = x;
        path.resize(0);
        while (helper != nullptr) {
            path.push_back(helper);
            helper = helper->parent;
        }
    };


    auto insertElement = [&](int ai) {
        // cerr << "inserting " << ai << endl;
        Node* p1 = tree.freeze_insert(ai, dirty, clean);
        Node* p1_copy = p1; //for deletion in the end

        find_path(p1);
        // cerr << "p1 st ed: " << p1->st << " " << p1->ed << endl;


        bool leftInclude = (p1->st == -inf) || game.compare(p1->st, ai);
        bool rightInclude = (p1->ed == inf) || game.compare(ai, p1->ed);
        int lastLeftBound = p1->st, lastRightBound = p1->ed;
        // cerr << "start: left and right bounds are " << lastLeftBound << " " << lastRightBound << endl;

        int minLeftInclude = path.size() - 1, minRightInclude = path.size() - 1;

        int st = 0, ed = 0;
        while (!leftInclude || !rightInclude)
        {
            st = ed;
            ed = min((int)path.size() - 1, max(ed + 1, ed * 2));
            if (ed == path.size() - 1) {
                leftInclude = true;
                rightInclude = true;
                minLeftInclude = min(minLeftInclude, ed);
                minRightInclude = min(minRightInclude, ed);
                break;
            }
            // cerr << "in expansion phase, trying the " << ed << "th node on the path" << endl;
            Node * tg = path[ed];
            if (!leftInclude&& tg->st != lastLeftBound) {
                leftInclude = (tg->st == -inf) || game.compare(tg->st, ai);
                lastLeftBound = tg->st;
            }
            if (!rightInclude && tg->ed != lastRightBound) {
                rightInclude = (tg->ed == inf) || game.compare(ai, tg->ed);
                lastRightBound = tg->ed;
            }
            if (leftInclude)    minLeftInclude = min(minLeftInclude, ed);
            if (rightInclude)   minRightInclude = min(minRightInclude, ed);
        }

        // cerr << "expansion ended, st = " << st << " ed = " << ed << endl;

        lastLeftBound = path[st]->st;
        lastRightBound = path[st]->ed;
        bool stLeftInclude = (minLeftInclude <= st);
        bool stRightInclude = (minRightInclude <= st);
        while (ed - st > 1)
        {
            int mid = (st + ed) >> 1;
            Node *tg = path[mid];

            if (!stLeftInclude) {
                if (tg->st != lastLeftBound && (tg->st == -inf || game.compare(tg->st, ai))){

                }
                else {
                    lastLeftBound = tg->st;
                    stLeftInclude = false;
                    st = mid;
                    continue;
                }
            }
            if (!stRightInclude) {
                if (tg->ed != lastRightBound && tg->ed == inf || game.compare(ai, tg->ed)) {
                }
                else {
                    lastRightBound = tg->ed;
                    stRightInclude = false;
                    lastLeftBound = tg->st;
                    stLeftInclude = true;
                    st = mid;
                    continue;
                }
            }
            ed = mid;
        }

        int turn_index = min(st + 1, ed);

        // cerr << "find turn: " << turn_index << endl;
        Node *turn = path[turn_index];

        if (turn->value == ai) {
            // cerr << "this insertion should take minimal clean compare" << endl;
            return;
        }
        // cerr << "needed to del and re insert " << ai << endl;
        tree.del(p1_copy);
        // cerr << "<<<<<<del<<<<<<" << " " << ai <<  endl;
        // tree.LinearPrint(tree.root);
        // cerr << "<<<<<<<<<<<<" << endl;
        Node* p2 = tree.insert(ai, dirty, clean, turn->value);

        // cerr << "<<<<<insert2<<<<<<<" << " " << ai <<  endl;
        // tree.LinearPrint(tree.root);
        // cerr << "<<<<<<<<<<<<" << endl;

        // cerr << "finished del and re insert " << ai << endl;
        // turn->priority = -inf + rand() % (2 * inf);
        // turn->priority = rand() - inf;
        // treap.rebalance(turn);
    };

    int n = game.getSize();
    shuffledA.resize(n);
    for (int i = 0; i < n; ++i)
        shuffledA[i] = i;
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffledA.begin(), shuffledA.end(), g);

    for (int ai : shuffledA) {
        insertElement(ai);

        indexes.resize(0);
        tree.LinearOutput(&indexes);

        // cerr << "after inserting " << ai << endl;
        // for (int i = 0; i < indexes.size(); ++i)
        //     cerr << indexes[i] << " ";
        // cerr << endl;
    }
        
    // exit(0);

    indexes.resize(0);
    tree.LinearOutput(&indexes);

    // cerr << "indexes final" << endl;
    // for (int i = 0; i < indexes.size(); ++i)
    //     cerr << indexes[i] << " ";
    // cerr << endl;



    index_to_rank();
}