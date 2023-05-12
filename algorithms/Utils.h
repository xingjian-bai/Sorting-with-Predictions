#pragma once
#include <vector>
#include "SortAlgo.h"

using namespace std;
const int inf = 1e8;
typedef function<bool(int, int)> Comp;

extern vector<vector<int>> buckets;



void new_pred();

void index_to_rank();

void output_to_file(vector<string> names, vector<std::vector<ll>> results, string filename);

double get_time();

typedef long long ll;
pair<vector<ll>, vector<ll>> parsePopulationData(const std::string &filename, int old);

vector<vector<bool>> parseTennisRelation(const string &filename, int size);

struct Node {
    int value, priority, st, ed, depth;
    Node *left, *right, *parent;

    Node(int value) : value(value), priority(rand()), st(-inf), ed(inf), left(nullptr), right(nullptr), parent(nullptr), depth(1) {}
};



class Treap {
public:
    Treap() : root(nullptr), rightmost(nullptr) {}

    Node* insert(int value, const Comp& dirty, const Comp& clean, int target = -1) {
        Node *newNode;
        tie(root, newNode) = insert(root, value, -inf, inf, dirty, clean, false, target);
        return newNode;
    }

    Node *root, *rightmost;

    int getDepth(Node *node) {
        if (node == nullptr)
            return 0;
        return node->depth;
    }
    int getPriority(Node *node) {
        if (node == nullptr)
            return -1e9;
        return node->priority;
    }

    Node *rotateRight(Node *y) {
        if (y == nullptr)
            return nullptr;
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
        if (x == nullptr)
            return nullptr;
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

        x->depth = max(getDepth(x->left), getDepth(x->right)) + 1;
        y->depth = max(getDepth(y->left), getDepth(y->right)) + 1;
        
        return y;
    }

    pair<Node*, Node*> insert(Node *node, int value, int st, int ed, const Comp& dirty, const Comp& clean, bool isClean, int target) {
        if (node == nullptr) {
            Node *newNode = new Node(value);
            newNode->st = st;
            newNode->ed = ed;
            return make_pair(newNode, newNode);
        }
        // cerr << "inserting " << value << " " << node->value << " " << isClean << endl;

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

        } 
        else {
            tie(node->right, newNode) = insert(node->right, value, node->value, ed, dirty, clean, isClean, target);
            node->right->parent = node;
        }

        if (getPriority(node->left)> node->priority) {
            node = rotateRight(node);
        }
        if (getPriority(node->right) > node->priority) {
            node = rotateLeft(node);
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
        cerr << node->value << " " << node->st << " " << node->ed << " par=" << (node->parent == nullptr ? -1 : node->parent->value) << endl;
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




extern vector<Node*> nodes;
class ScapegoatTree {
public:
    ScapegoatTree() : root(nullptr), rightmost(nullptr) {}

    Node* insert(int value, const function<bool(int, int)>& dirty, const function<bool(int, int)>& clean, int target = -1) {
        Node *newNode;
        tie(root, newNode) = insert(root, value, -inf, inf, dirty, clean, false, target);
        return newNode;
    }

    Node *root, *rightmost;

    int getDepth(Node *node) {
        if (node == nullptr)
            return 0;
        return node->depth;
    }

    const double ALPHA = 1.5;
    bool isScapegoat(Node *node) {
        if (!node || !node->parent) return false;
        double large = max(getDepth(node->parent->left), getDepth(node->parent->right));
        double small = min(getDepth(node->parent->left), getDepth(node->parent->right));
        return large > ALPHA * (small + 1);
    }


    pair<Node*, Node*> insert(Node *node, int value, int st, int ed, const function<bool(int, int)>& dirty, const function<bool(int, int)>& clean, bool isClean, int target) {
        if (node == nullptr) {
            Node *newNode = new Node(value);
            newNode->st = st;
            newNode->ed = ed;
            return make_pair(newNode, newNode);
        }

        if (node->value == target)
            isClean = true;

        function<bool(int, int)> comp = isClean ? clean : dirty;
        if (node->value == target)
            comp = [&](int a, int b) {return !dirty(a, b);};

        Node *newNode;
        if (comp(value, node->value)) {
            tie(node->left, newNode) = insert(node->left, value, st, node->value, dirty, clean, isClean, target);
            node->left->parent = node;
        } else {
            tie(node->right, newNode) = insert(node->right, value, node->value, ed, dirty, clean, isClean, target);
            node->right->parent = node;
        }

        node->depth = max(getDepth(node->left), getDepth(node->right)) + 1;

        if (isScapegoat(node)) {
            node = rebuild(node);
            updateAncestors(node);
        }

        if (node->left) node->st = node->left->st;
        if (node->right) node->ed = node->right->ed;

        assert(node != nullptr);
        return make_pair(node, newNode);
    }

    Node* rebuild(Node *node) {
        if (!node) return nullptr;
        nodes.resize(0);
        flatten(node, nodes);
        Node *new_root = buildBalanced(nodes, 0, nodes.size() - 1);
        
        return new_root;
    }

    void flatten(Node *node, vector<Node*>& nodes) {
        if (!node) return;
        flatten(node->left, nodes);
        nodes.push_back(node);
        flatten(node->right, nodes);
        node->left = node->right = nullptr;
    }

    Node* buildBalanced(vector<Node*>& nodes, int l, int r) {
        if (l > r) return nullptr;
        int mid = (l + r) / 2;
        Node *root = nodes[mid];
        root->left = buildBalanced(nodes, l, mid - 1);
        if (root->left) root->left->parent = root;
        root->right = buildBalanced(nodes, mid + 1, r);
        if (root->right) root->right->parent = root;
        root->depth = max(getDepth(root->left), getDepth(root->right)) + 1;
        return root;
    }

    void updateAncestors(Node *node) {
        if (!node)
            return;
        if (node->parent) {
            node->parent->depth = max(getDepth(node->parent->left), getDepth(node->parent->right)) + 1;
            updateAncestors(node->parent);
        }
    }

    void LinearOutput(vector<int> *ranking) const {LinearOutput(root, ranking);}
    static void LinearOutput(const Node *node, vector<int> *ranking) {
        if (node == nullptr) return;
        LinearOutput(node->left, ranking);
        ranking->push_back(node->value);
        LinearOutput(node->right, ranking);
    }
};