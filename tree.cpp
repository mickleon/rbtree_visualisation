#include <iostream>
#include <vector>
#include <cmath>

#include "tree.h"

void print_space(int n){
    if (n < 1)
        return;
    std::string s(n, ' ');
    std::cout << s;
}

void Tree::left_rotate(Node *p) {
    if (!p || !p->right) return;
    Node* c = p->right;       
    p->right = c->left;
    if (c->left)
        c->left->parent = p;
    c->parent = p->parent;
    if (!c->parent) {
        Tree::root = c;
    } else if (p == p->parent->left)
        p->parent->left = c;
    else
        p->parent->right = c;
    c->left = p;
    p->parent = c;
}

void Tree::right_rotate(Node *p) {
    if (!p || !p->left) return;
    Node *c = p->left;
    p->left = c->right;
    if (c->right)
        c->right->parent = p;
    c->parent = p->parent;
    if (!c->parent) {
        Tree::root = c;
    } else if (p == p->parent->right)
        p->parent->right = c;
    else
        p->parent->left = c;
    c->right = p;
    p->parent = c;
}

Node* Tree::grandparent(Node* x) {
    if (!x || !x->parent)
        return nullptr;
    return x->parent->parent;
}

Node* Tree::uncle(Node* x) {
    Node* g = grandparent(x);
    if (!g)
        return nullptr;
    if (x->parent == g->left)
        return g->right;
    else
        return g->left;
}

Node* Tree::sibling(Node* x) {
    if (x && x->parent) {
        if (x == x->parent->left)
            return x->parent->right;
        else
            return x->parent->left;
    }
    return nullptr;
}

void Tree::insert(int value) {
    Node* node = new Node(value);
    if (!Tree::root) {
        Tree::root = node;
        return;
    }
    Node* temp = Tree::root;
    while (temp) {
        if (node->inf > temp->inf) {
            if (temp->right)
                temp = temp->right;
            else {
                temp->right = node;
                node->parent = temp;
                break;
            }
        } else if (node->inf < temp->inf) {
            if (temp->left)
                temp = temp->left;
            else {
                temp->left = node;
                node->parent = temp;
                break;
            }
        } else {
            delete node;
            return;
        }
    }
}

Node* Tree::find(Node *node, int value) {
    if (!node || node->inf == value)
        return node;
    if (value < node->inf)
        return Tree::find(node->left, value);
    return Tree::find(node->right, value);
}

Node* Tree::find(int value) {
    return Tree::find(Tree::root, value);
}

void Tree::erase(Node *node) {
    Node *p = node->parent;
    if (!node->left && !node->right) { // No children
        if (!p) // Only one node in tree
            Tree::root = nullptr;
        else {
            if (p->left == node) p->left = nullptr;
            else if (p->right == node) p->right = nullptr;
        }
        delete node;
    }
    else if (!node->left || !node->right) { // 1 child
        Node *child = node->left ? node->left : node->right;
        if (!p) // Root
            Tree::root = child;
        else {
            if (p->left == node) p->left = child;
            else if (p->right == node) p->right = child;
        }
        child->parent = p;
        delete node;
    } else { // 2 childer
        Node *succ = Tree::min(node->right);
        node->inf = succ->inf;
        if (succ->parent->left == succ) 
            succ->parent->left = succ->right;
        else
            succ->parent->right = succ->right;
        if (succ->right)
            succ->right->parent = succ->parent;
        delete succ;
    }
}

Node* Tree::max(Node *node) {
    if (!node)
        return nullptr;
    Node* y = node;
    while (y->right)
        y = y->right;
    return y;
}

Node* Tree::max() {
    return Tree::max(Tree::root);
}

Node* Tree::min(Node *node) {
    if (!node)
        return nullptr;
    Node* y = node;
    while (y->left)
        y = y->left;
    return y;
}

Node* Tree::min() {
    return Tree::min(Tree::root);
}

int Tree::height(Node* node) {
    if (!node)
        return 0;
    return 1 + std::max(Tree::height(node->left),
        Tree::height(node->right));
}

int Tree::height() {
    if (!Tree::root)
        return 0;
    return 1 + std::max(Tree::height(Tree::root->left),
        Tree::height(Tree::root->right));
}

// Traversal with depth calculation and node offset from the left edge of the level
void Tree::make_array(Node *node, int depth, int count) {
    Tree::array[depth].push_back({node, count - (1 << depth)});
    if (node->left) 
        Tree::make_array(node->left, depth + 1, count*2);
    if (node->right) 
        Tree::make_array(node->right, depth + 1, count*2 + 1);     
}

// The number of characters to output the number
int digit_count(int x) {
    if (x > 0)  
        return log10(x) + 1;
    else if (x < 0)
        return log10(abs(x)) + 2;
    else
        return 1;
}

void print_node(Node *node, int d) {
    if (!node)
        printf("%*c", d, 'n');
    else
        printf("%*d", d, node->inf);
}

// Function for tree output
void Tree::print(){
    if (Tree::root == nullptr) {
        printf("NULL TREE\n");
        return;
    }
    int height = Tree::height();
    Tree::array.assign(height, {});
    Tree::make_array(Tree::root);

    // Maximum number of characters of node value in tree 
    int d = std::max(digit_count(Tree::max()->inf),
        digit_count(Tree::min()->inf));
    // Space at the beginning of each level
    int init_space = height > 1 ? (d + 1)*(1 << (height - 2)) : 0;
    for (int depth = 0; depth < height; depth++) {
        print_space(init_space - d);
        // Space between nodes at this level
        int space = init_space * 2 - d;
        if (space == 0)
            space = 1;

        int prev_offset = 0;
        for (auto &node : Tree::array[depth]) {
            // Calculate indentation if the tree is incomplete
            print_space((space + d)*(node.second - prev_offset));
            print_node(node.first, d);
            // Space after the node
            print_space(space);
            // Save offset for subsequent calculations
            prev_offset = node.second + 1;
        }
        printf("\n");
        init_space /= 2;
    }
}

void Tree::clear(Node* node) {
    if (node) {
        Tree::clear(node->left);
        Tree::clear(node->right);
        delete node;
    }
}
