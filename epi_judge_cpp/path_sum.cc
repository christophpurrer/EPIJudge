#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>> &node,
                      int sum_so_far,
                      int target_sum) {
    if (!node) return false;

    sum_so_far += node->data;
    if (!node->left && !node->right && sum_so_far == target_sum) {
        return true;
    }

    return HasPathSumHelper(node->left, sum_so_far, target_sum) ||
           HasPathSumHelper(node->right, sum_so_far, target_sum);
}

bool HasPathSum(const unique_ptr<BinaryTreeNode<int>> &tree,
                int target_sum) {
    return HasPathSumHelper(tree, 0, target_sum);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  return GenericTestMain(args, "path_sum.cc", "path_sum.tsv", &HasPathSum,
                         DefaultComparator{}, param_names);
}
