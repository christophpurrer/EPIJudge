#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct BalancedAndHeight {
    bool isBalanced;
    int height;
};

BalancedAndHeight IsBalancedHelper(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (!tree) return {true, -1};

    auto left = IsBalancedHelper(tree->left);
    if (!left.isBalanced) {
        return left;
    }
    auto right = IsBalancedHelper(tree->right);
    if (!right.isBalanced) {
        return right;
    }

    bool isBalanced = std::abs(left.height - right.height) <= 1;
    int height = std::max(left.height, right.height) + 1;
    return {isBalanced, height};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return IsBalancedHelper(tree).isBalanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
