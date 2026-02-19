#ifndef TREE_H
#define TREE_H
#include <vector>

struct Node {
    int inf;
    Node *left, *right;
    Node *parent;
    char color;

    Node(int value): inf(value), left(nullptr), right(nullptr), parent(nullptr), color('r') {}
};

class RBTree {
public:
    RBTree(): root(nullptr) {}

    ~RBTree() { clear(this->root); }

    void insert(int value);
    void erase(int value);
    Node *find(int value);
    Node *max();
    Node *min();
    void print(bool show_null_leaves = false);
    void clear();

private:
    Node *root;
    void right_rotate(Node *p);
    void left_rotate(Node *p);
    void insert_fixup(Node *node);
    void erase_node(Node *node);
    void erase_fixup(Node *p);
    Node *find(Node *node, int value);
    Node *max(Node *node);
    Node *min(Node *node);
    void clear(Node *node);
    int height(Node *node);
    int height();
    void make_array(
        std::vector<std::vector<Node *>> &array, Node *node, bool show_null_leaves = false,
        int depth = 0, int count = 1
    );
};
#endif
