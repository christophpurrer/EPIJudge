#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

// Approach1: Recursive with lowerBound and upperBound
bool IsBinaryTreeBSTHelperRec(BinaryTreeNode<int> *node, int lowerBound, int upperBound) {
    if (!node) return true;
    if (node->data < lowerBound || node->data > upperBound) return false;

    return IsBinaryTreeBSTHelperRec(node->left.get(), lowerBound, node->data) &&
           IsBinaryTreeBSTHelperRec(node->right.get(), node->data, upperBound);
}

// Approach2: Exploit the InOrderTraversal property
bool IsBinaryTreeBSTHelperInOrderHelper(BinaryTreeNode<int> *node, int &lastValue) {
    // reached leaf
    if (!node) return true;
    // goLeft
    if (!IsBinaryTreeBSTHelperInOrderHelper(node->left.get(), lastValue)) {
        return false;
    }
    // visit node
    if (node->data < lastValue) {
        return false;
    }
    lastValue = node->data;
    // goRight
    return IsBinaryTreeBSTHelperInOrderHelper(node->right.get(), lastValue);
}

bool IsBinaryTreeBSTHelperInOrder(BinaryTreeNode<int> *node) {
    int lastValue = std::numeric_limits<int>::min();
    return IsBinaryTreeBSTHelperInOrderHelper(node, lastValue);
}

// Approach3: BFS approach
struct QueueEntry {
    const std::unique_ptr<BinaryTreeNode<int>>& node;
    int lowerBound, upperBound;
};

bool IsBinaryTreeBSTBFS(const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::queue<QueueEntry> queue;
    queue.emplace(QueueEntry{tree, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()});

    while (!queue.empty()) {
        // process node
        auto entry = queue.front();
        if (entry.node->data < entry.lowerBound || entry.node->data > entry.upperBound) return false;

        // enqueue left
        if (entry.node->left) {
            queue.emplace(QueueEntry{entry.node->left, entry.lowerBound, entry.node->data});
        }

        // enqueue right
        if (entry.node->right) {
            queue.emplace(QueueEntry{entry.node->right, entry.node->data, entry.upperBound});
        }
        queue.pop();
    }
    return true;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>> &tree) {
    return IsBinaryTreeBSTHelperRec(tree.get(), std::numeric_limits<int>::min(),
                                    std::numeric_limits<int>::max())
           && IsBinaryTreeBSTHelperInOrder(tree.get())
           && IsBinaryTreeBSTBFS(tree);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
