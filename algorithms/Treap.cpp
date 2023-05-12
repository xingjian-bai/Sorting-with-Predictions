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
        cerr << "inserting " << value << " " << st << " " << ed << " " << node << endl;
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