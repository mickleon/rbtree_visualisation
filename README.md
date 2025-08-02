# What is this?

There is C++ class for red/black tree, that have method for **console output** for tree **without any specific libraries**. The program correctly outputs numbers **with any number of digits**.

# What is it for?

This is a training example of a red/black tree. This may be necessary for those who study C++ and dynamic structures such as trees.

# Run

```bash
g++ main.cpp tree.cpp -o main && ./main
```

# User API

The following functions are available for working with tree:

- `void Tree::insert(int value)`: inserts node with value `value` to a tree and calls the fixup function.
- `void Tree::erase(Node *node)`: erases the node with value `value` from tree and calls the fixup function.
- `Node* Tree::find(int value)`: returns a pointer to a node in the tree with the value `value`.
- `Node* Tree::max()`: returns a pointer to a node in the tree with the maximal value.
- `Node* Tree::min()`: returns a pointer to a node in the tree with the minimal value.
- `void Tree::print(bool show_null_leaves = false)`: outputs the tree to the console. It has optional parameter `show_null_leaves` that is false by default, responsible for displaying null leaves.
- `void clear()`: erases all the nodes from the tree.

# Example of output

![Tree output](/img/tree_output.png)

With null leaves: 

![Tree output with null leaves](/img/tree_output_null_leaves.png)