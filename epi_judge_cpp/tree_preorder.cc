#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;

void PreorderTraversalHelper(const unique_ptr<BinaryTreeNode<int>> &tree, std::vector<int> &result) {
    if (!tree) return;
    result.emplace_back(tree->data);
    PreorderTraversalHelper(tree->left, result);
    PreorderTraversalHelper(tree->right, result);
}

vector<int> PreorderTraversalRec(const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::vector<int> result;
    PreorderTraversalHelper(tree, result);
    return result;
}

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::vector<int> result;
    std::stack<BinaryTreeNode<int> *> stack;
    stack.emplace(tree.get());
    while (!stack.empty()) {
        auto cur = stack.top();
        result.emplace_back(cur->data);
        stack.pop();
        if (cur->right) {
            stack.push(cur->right.get());
        }
        if (cur->left) {
            stack.push(cur->left.get());
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
