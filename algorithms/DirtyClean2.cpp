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
const int inf = 1e8;

struct Node {
    int value, priority, st, ed, depth;
    Node *left, *right, *parent;

    Node(int value) : value(value), priority(rand()), st(-inf), ed(inf), left(nullptr), right(nullptr), parent(nullptr), depth(1) {}
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

    int getDepth(Node *node) {
        if (node == nullptr)
            return 0;
        return node->depth;
    }

    Node *rotateRight(Node *y) {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->right = y;
        x->parent = y->parent;
        y->parent = x;

        x->ed = y->ed;
        y->st = x->value;

        y->depth = max(getDepth(y->left), getDepth(y->right)) + 1;
        x->depth = max(getDepth(x->left), getDepth(x->right)) + 1;
        return x;
    }

    Node *rotateLeft(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->left = x;
        y->parent = x->parent;
        x->parent = y;

        y->st = x->st;
        x->ed = y->value;

        y->depth = max(getDepth(y->left), getDepth(y->right)) + 1;
        x->depth = max(getDepth(x->left), getDepth(x->right)) + 1;
        return y;
    }

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
            if (node->left->priority > node->priority) {
                node = rotateRight(node);
            }
            if (node->right->priority > node->priority) {
                node = rotateLeft(node);
            }
        } 
        else {
            tie(node->right, newNode) = insert(node->right, value, node->value, ed, dirty, clean, isClean, target);
            node->right->parent = node;
        }

        // Update st and ed values
        if (node->left)     node->st = node->left->st;
        if (node->right)    node->ed = node->right->ed;

        assert(node!=nullptr);
        node->depth = max(getDepth(node->left), getDepth(node->right)) + 1;
        return make_pair(node, newNode);
    }

    void LinearOutput(vector<int> *ranking) const {LinearOutput(root, ranking);}
    static void LinearOutput(const Node *node, vector<int> *ranking) {
        if (node == nullptr) return;
        LinearOutput(node->left, ranking);
        ranking->push_back(node->value);
        LinearOutput(node->right, ranking);
    }

    static void LinearPrint(const Node *node) {
        if (node == nullptr) return;
        LinearPrint(node->left);
        cerr << node->value << " ";
        LinearPrint(node->right);
    }

    void deleteNode(Node *node) {
        if (!node)
            return ;
        Node *parent = node;
        deleteNodeHelper(node);
        while (parent) {
            // cerr << "???" << endl;
            parent->depth = max(getDepth(parent->left), getDepth(parent->right)) + 1;
            parent = parent->parent;
        }
    }

    void deleteNodeHelper(Node *node_to_be_deleted) {
        if (!node_to_be_deleted)
            return ;

        Node *parent = node_to_be_deleted->parent;

        if (!node_to_be_deleted->left || !node_to_be_deleted->right) {
            Node *temp = node_to_be_deleted->left ? node_to_be_deleted->left : node_to_be_deleted->right;

            if (parent) {
                if (parent->left == node_to_be_deleted)
                    parent->left = temp;
                else
                    parent->right = temp;

                if (temp)
                    temp->parent = parent;
                parent->depth = max(getDepth(parent->left), getDepth(parent->right)) + 1;
            } else {
                root = temp;
                if (temp)
                    temp->parent = nullptr;
            }
            delete node_to_be_deleted;
        }
        else {
            if (node_to_be_deleted->left->priority < node_to_be_deleted->right->priority) {
                node_to_be_deleted = rotateRight(node_to_be_deleted);
                deleteNodeHelper(node_to_be_deleted->right);

            } else {
                node_to_be_deleted = rotateLeft(node_to_be_deleted);
                deleteNodeHelper(node_to_be_deleted->left);
            }
            if (node_to_be_deleted)
                node_to_be_deleted->depth = max(getDepth(node_to_be_deleted->left), getDepth(node_to_be_deleted->right)) + 1;
        }

        if (parent) {
            if (parent->left)  parent->st = parent->left->st;
            if (parent->right) parent->ed = parent->right->ed;
        }
        return ;
    }

    void rebalance(Node *node) {
        if (!node)
            return;

        bool left_rotation_required = node->left && node->left->priority > node->priority;
        bool right_rotation_required = node->right && node->right->priority > node->priority;

        bool isRoot = !node->parent;
        bool isLeft = node->parent && node->parent->left == node;
        bool isRight = node->parent && node->parent->right == node;



        if (left_rotation_required && getDepth(node->left) > getDepth(node->right)) {
            node = rotateRight(node);
            rebalance(node->left);
        } 
        else if (right_rotation_required && getDepth(node->right) > getDepth(node->left)) {
            node = rotateLeft(node);
            rebalance(node->right);
        }
        else if (left_rotation_required) {
            node = rotateRight(node);
            rebalance(node->left);
        }
        else if (right_rotation_required) {
            node = rotateLeft(node);
            rebalance(node->right);
        }

        if (isRoot)
            root = node;
        else {
            if (isLeft)
                node->parent->left = node;
            else
                node->parent->right = node;
            assert(node->parent!=nullptr);
            node->parent->depth = max(getDepth(node->parent->left), getDepth(node->parent->right)) + 1;
        }
        
    }

};


std::vector<int> DirtyClean2::sort(SortGame &game)
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

    // prefix sum
    return index_to_rank(sorted);
}