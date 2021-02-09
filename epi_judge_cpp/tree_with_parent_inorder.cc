#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

void InorderTraversalHelper(const unique_ptr<BinaryTreeNode<int>> &tree, vector<int> &result) {
    if (!tree) return;
    InorderTraversalHelper(tree->left, result);
    result.emplace_back(tree->data);
    InorderTraversalHelper(tree->right, result);
}

vector<int> InorderTraversalRec(const unique_ptr<BinaryTreeNode<int>> &tree) {
    vector<int> result;
    InorderTraversalHelper(tree, result);
    return result;
}

void RecLeft(std::stack<BinaryTreeNode<int> *> &stack, BinaryTreeNode<int> *node) {
    while (node) {
        stack.emplace(node);
        node = node->left.get();
    }
}

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::stack<BinaryTreeNode<int>*> stack;
    RecLeft(stack, tree.get());
    vector<int> result;
    while(!stack.empty()) {
        auto value = stack.top();
        stack.pop();
        RecLeft(stack, value->right.get());
        result.emplace_back(value->data);
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
