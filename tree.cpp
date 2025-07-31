#include <iostream>
#include <vector>
#include <cmath>

#include "tree.h"

// Rotates the tree to the left around the node `p`
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

// Rotates the tree to the right around the node `p`
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

// Returns the grandparent of node `x`
Node* Tree::grandparent(Node* x) {
    if (!x || !x->parent)
        return nullptr;
    return x->parent->parent;
}

// Returns the uncle of node `x`
Node* Tree::uncle(Node* x) {
    Node* g = grandparent(x);
    if (!g)
        return nullptr;
    if (x->parent == g->left)
        return g->right;
    else
        return g->left;
}

// Returns the sibling of node `x`
Node* Tree::sibling(Node* x) {
    if (x && x->parent) {
        if (x == x->parent->left)
            return x->parent->right;
        else
            return x->parent->left;
    }
    return nullptr;
}

// Inserts node with value `value` to a tree and calls the fixup function
void Tree::insert(int value) {
    Node* node = new Node(value);
    if (!Tree::root) {
        node->color = 'b';
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
    Tree::insert_fixup(node);
}

// Auxullary function for `insert`, it does a fixup of a tree
// Expected node `node` is not a root
void Tree::insert_fixup(Node *node) {
    Node *p = node->parent;
    if (p->color == 'r') { // Parent is red
        Node *u = sibling(p);
        if (u && u->color == 'r') { // Uncle is red
            p->color = u->color = 'b';
            Node *g = p->parent;
            if (g->parent) {
                g->color = 'r';
                Tree::insert_fixup(g);
            }
        }
        else { // Uncle is black
            Node *g = p->parent;
            if (node == p->left) {
                if (p == g->left)
                    Tree::right_rotate(g);
                else {
                    Tree::right_rotate(p);
                    p = p->parent;
                    g = p->parent;
                    Tree::left_rotate(g);
                }
            } else {
                if (p == g->right)
                    Tree::left_rotate(g);
                else {
                    Tree::left_rotate(p);
                    p = p->parent;
                    g = p->parent;
                    Tree::right_rotate(g);
                }
            }
            std::swap(g->color, p->color);
        }
    }
}

// Erases the node with value `value` from tree and calls the fixup function
void Tree::erase(int value) {
    Node *node = Tree::find(value);
    if (node)
        Tree::erase_node(node);
}

// Erases the node `node` from tree and calls the fixup function
void Tree::erase_node(Node* node) {
    Node *p = node->parent;
    if (!node->left && !node->right) { // No children
        if (!p) // Root
            Tree::root = nullptr;
        else {
            if (p->left == node)
                p->left = nullptr;
            else
                p->right = nullptr;
        }
        delete node;
        return;
    }
    if (!node->left || !node->right) { // 1 child
        Node *child = node->left ? node->left : node->right;
        if (!p) { // Root
            Tree::root = child;
        } else {
            if (p->left == node)
                p->left = child;
            else
                p->right = child;
        }
        child->parent = p;
        delete node;
        return;
    }
    // 2 childer
    Node *succ = Tree::min(node->right);
    std::swap(succ->inf, node->inf);
    Tree::erase_node(succ);
}

// Returns a pointer to a node in the subtree `node` with the value `value`
Node* Tree::find(Node *node, int value) {
    if (!node || node->inf == value)
        return node;
    if (value < node->inf)
        return Tree::find(node->left, value);
    return Tree::find(node->right, value);
}

// Overload of previous function, where `node` is a tree root `Tree::root`
Node* Tree::find(int value) {
    return Tree::find(Tree::root, value);
}

// Returns a pointer to a node in the subtree `node` with the maximal value
Node* Tree::max(Node *node) {
    if (!node)
        return nullptr;
    Node* y = node;
    while (y->right)
        y = y->right;
    return y;
}

// Overload of previous function, where `node` is a tree root `Tree::root`
Node* Tree::max() {
    return Tree::max(Tree::root);
}

// Returns a pointer to a node in the subtree `node` with the minimal value
Node* Tree::min(Node *node) {
    if (!node)
        return nullptr;
    Node* y = node;
    while (y->left)
        y = y->left;
    return y;
}

// Overload of previous function, where `node` is a tree root `Tree::root`
Node* Tree::min() {
    return Tree::min(Tree::root);
}

int Tree::height(Node* node) {
    if (!node)
        return 0;
    return 1 + std::max(Tree::height(node->left),
        Tree::height(node->right));
}

// Overload of previous function, where `node` is a tree root `Tree::root`
int Tree::height() {
    if (!Tree::root)
        return 0;
    return 1 + std::max(Tree::height(Tree::root->left),
        Tree::height(Tree::root->right));
}

// Traversal with depth calculation and node offset from the left edge of the level
void Tree::make_array(Node *node, bool show_null_leaves, int depth, int count) {
    Tree::array[depth].push_back({node, count - (1 << depth)});
    if (node->left) 
        Tree::make_array(node->left, show_null_leaves, depth + 1, count*2);
    else if (show_null_leaves)
        Tree::array[depth + 1]
            .push_back({nullptr, count*2 - (1 << depth+1)});
    if (node->right) 
        Tree::make_array(node->right, show_null_leaves, depth + 1, count*2 + 1);
    else if (show_null_leaves)
        Tree::array[depth + 1]
            .push_back({nullptr, (count*2 + 1) - (1 << depth+1)});        
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

// Auxulary function for the `print`, it outputs one node `node`, fills up to `d` characters with spaces
void print_node(Node *node, int d) {
    if (!node)
        printf("%*c", d, 'n');
    else if (node->color == 'r')
        printf("\033[31m%*ld\033[0m", d, static_cast<long>(node->inf));
    else
        printf("%*ld", d, static_cast<long>(node->inf));
}

// Prints space n times
void print_space(int n){
    if (n < 1)
        return;
    std::string s(n, ' ');
    std::cout << s;
}

// Function for tree output
void Tree::print(bool show_null_leaves){
    if (Tree::root == nullptr) {
        printf("NULL TREE\n");
        return;
    }
    int height = Tree::height();
    if (show_null_leaves)
        height++;
    Tree::array.assign(height, {});
    Tree::make_array(Tree::root, show_null_leaves);

    // Maximum number of digit of node in tree 
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

// Erases all the nodes from the subtree `node`
void Tree::clear(Node* node) {
    if (node) {
        Tree::clear(node->left);
        Tree::clear(node->right);
        delete node;
    }
}

// Overload of previous function, where `node` is a tree root `Tree::root`
void Tree::clear() {
    if (Tree::root) {
        Tree::clear(Tree::root->left);
        Tree::clear(Tree::root->right);
        delete Tree::root;
    }
}
