# What is this?

There is C++ class for red black tree, that have method for **console output** for tree **without any specific libraries**. The program correctly outputs numbers **with any number of digits**.

# What is it for?

This is a training example of a red black tree. This may be necessary for those who study C++ and dynamic structures such as trees.

# Run

```bash
g++ main.cpp tree.cpp -o main && ./main
```

# API

The following functions are available for working with tree:

- `void Tree::insert(int value)`: inserts node with value `value` to a tree and calls the fixup function.
- `void Tree::erase(Node *node)`: erases the node `node` from tree (now without a fixup).
- `Node* Tree::find(Node *node, int value)`: returns a pointer to a node in the subtree `node` with the value `value`.
- `Node* Tree::find(int value)`: overload of previous function, where `node` is a tree roor `Tree::root`.
- `Node* Tree::max(Node *node)`: returns a pointer to a node in the subtree `node` with the maximal value.
- `Node* Tree::max()`: overload of previous function, where `node` is a tree roor `Tree::root`.
- `Node* Tree::min(Node *node)`: returns a pointer to a node in the subtree `node` with the minimal value.
- `Node* Tree::min()`: overload of previous function, where `node` is a tree roor `Tree::root`.
- `void Tree::print(bool show_null_leaves = false)`: outputs the tree to the console. It has optional parameter `show_null_leaves` that is false by default, responsible for displaying null leaves

# Example of output

![Tree output](/img/tree_output.png)

With null leaves: 

![Tree output with null leaves](/img/tree_output_null_leaves.png)