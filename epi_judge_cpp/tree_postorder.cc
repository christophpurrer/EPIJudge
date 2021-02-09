#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

void PostorderTraversalHelper(const unique_ptr<BinaryTreeNode<int>> &tree, std::vector<int> &result) {
    if (!tree) return;
    PostorderTraversalHelper(tree->left, result);
    PostorderTraversalHelper(tree->right, result);
    result.emplace_back(tree->data);
}

vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::vector<int> result;
    PostorderTraversalHelper(tree, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_postorder.cc", "tree_postorder.tsv",
                         &PostorderTraversal, DefaultComparator{}, param_names);
}
