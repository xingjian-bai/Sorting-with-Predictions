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
const int inf = 1e9;

struct Node {
    int value, priority, st, ed, depth;
    Node *left, *right, *parent;

    Node(int value) : value(value), priority(rand()), st(-inf), ed(inf), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Treap {
public:
    Treap() : root(nullptr) {}

    Node* insert(int value, const Comp& dirty, const Comp& clean, int target = -1) {
        Node *newNode;
        tie(root, newNode) = insert(root, value, -inf, inf, dirty, clean, false, target);
        return newNode;
    }

    Node *root;

        // Node *rotateRight(Node *y) {
    //     Node *x = y->left;
    //     y->left = x->right;
    //     if (x->right != nullptr) {
    //         x->right->parent = y;
    //     }
    //     x->right = y;
    //     x->parent = y->parent;
    //     y->parent = x;

    //     x->ed = y->ed;
    //     y->st = x->value;
    //     return x;
    // }

    // Node *rotateLeft(Node *x) {
    //     Node *y = x->right;
    //     x->right = y->left;
    //     if (y->left != nullptr) {
    //         y->left->parent = x;
    //     }
    //     y->left = x;
    //     y->parent = x->parent;
    //     x->parent = y;

    //     y->st = x->st;
    //     x->ed = y->value;
    //     return y;
    // }

    pair<Node*, Node*> insert(Node *node, int value, int st, int ed, const Comp& dirty, const Comp& clean, bool isClean, int target) {
        if (node == nullptr) {
            Node *newNode = new Node(value);
            newNode->st = st;
            newNode->ed = ed;
            return make_pair(newNode, newNode);
        }

        if (node->value == target)
            isClean = true;

        Node *newNode;
        Comp comp = isClean ? clean : dirty;
        if (node->value == target)
            //comp is the inverse of dirty
            comp = [&](int a, int b) {return !dirty(a, b);};

        if (comp(value, node->value))
        {
            tie(node->left, newNode) = insert(node->left, value, st, node->value, dirty, clean, isClean, target);
            node->left->parent = node;
            // if (node->left->priority > node->priority) {
            //     node = rotateRight(node);
            // }
            // if (node->right->priority > node->priority) {
            //     node = rotateLeft(node);
            // }
        } 
        else {
            tie(node->right, newNode) = insert(node->right, value, node->value, ed, dirty, clean, isClean, target);
            node->right->parent = node;
        }

        // Update st and ed values
        if (node->left)     node->st = node->left->st;
        if (node->right)    node->ed = node->right->ed;

        return make_pair(node, newNode);
    }

    void LinearOutput(vector<int> *ranking) const {LinearOutput(root, ranking);}
    static void LinearOutput(const Node *node, vector<int> *ranking) {
        if (node == nullptr) return;
        LinearOutput(node->left, ranking);
        ranking->push_back(node->value);
        LinearOutput(node->right, ranking);
    }

    void delete_leaf(Node *node) {
        if (node->parent == nullptr) {
            root = nullptr;
            return;
        }
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    }
};


int counter[10010];
std::vector<int> DirtyClean::sort(SortGame &game)
{
    memset(counter, 0, sizeof(counter));
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

    int opt_counter = 0, binary_counter = 0;

    auto insertElement = [&](int ai) {
        // cerr << "insert " << ai << endl;
        Node* p1 = treap.insert(ai, dirty, clean);
        Node* p1_copy = p1, * p1_up = p1;

        path.resize(0);
        while (p1_up != nullptr) {
            path.push_back(p1_up);
            p1_up = p1_up->parent;
        }

        bool leftInclude = (p1->st == -inf) || game.compare(p1->st, ai);
        bool rightInclude = (p1->ed == inf) || game.compare(ai, p1->ed);

        int minLeftInclude = inf, minRightInclude = inf;

        int st = 0, ed = 0;

        while (!leftInclude || !rightInclude)
        {
            st = ed;
            ed = min((int)path.size() - 1, max(ed + 1, ed * 2));
            Node * tg = path[ed];
            binary_counter--;
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
                binary_counter--;
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
                binary_counter--;
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

        counter[ed]++;

        binary_counter += ed * 2;

        // cerr << "min inclusion: " << ed << endl;
        Node * turn = path[ed];

        if (turn->value == ai)    return;
        
        treap.delete_leaf(p1_copy);

        Node* p2 = treap.insert(ai, dirty, clean, turn->value);
        opt_counter += 1;
        // cerr << "finished insert" << endl;
    };

    int n = game.getSize();
    vector<int> shuffledA(n);
    for (int i = 0; i < n; ++i)    shuffledA[i] = i;


    random_device rd;
    mt19937 g(rd());
    shuffle(shuffledA.begin(), shuffledA.end(), g);

    for (int ai : shuffledA)
    // for (int ai = 0; ai < n; ++ai)
        insertElement(ai);

    vector<int> sorted;
    treap.LinearOutput(&sorted);
    // cerr << "opt_counter: " << opt_counter << endl;
    // cerr << "binary_counter: " << binary_counter << endl;

    // prefix sum
    for (int i = 10000; i >= 0; --i)
        counter[i] += counter[i + 1];
    // for (int i = 0; i < 30; ++i)
    //     cerr << counter[i] << " ";
    // cerr << endl;
    return index_to_rank(sorted);
}