#ifndef TREE_H
    #define TREE_H
    #include <vector>

    struct Node {
        int inf;
        Node *left, *right;
        Node *parent;
        char color;
        Node (int value):
        inf(value), left(nullptr), right(nullptr), parent(nullptr), color('r') {}
    };

    class Tree {
    public:
        Tree(): root(nullptr) {};
        ~Tree() {clear(root);}
        void insert(int value);
        void erase(Node *node);
        Node* find(Node *node, int value);
        Node* find(int value);
        Node* max(Node *node);
        Node* max();
        Node* min(Node *node);
        Node* min();
        void print(bool show_null_leaves = false);
    private:
        std::vector<std::vector<std::pair<Node*, int>>> array;
        Node* root;
        void right_rotate(Node *p);
        void left_rotate(Node *p);
        Node* grandparent(Node* x);
        Node* uncle(Node* x);
        Node* sibling(Node* x);
        void insert_fixup(Node *node);
        int height(Node *node);
        int height();
        void make_array(Node *node, bool show_null_leaves = false, int depth = 0, int count = 1);
        void clear(Node* node);
    };
#endif
