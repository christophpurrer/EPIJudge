#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(const vector<int> &preorder,
                                                                    size_t preorder_start, size_t preorder_end,
                                                                    size_t inorder_start, size_t inorder_end,
                                                                    std::map<int, size_t> node_to_inorder_index) {
    if (preorder_end <= preorder_start || inorder_end <= inorder_start) {
        return nullptr;
    }
    auto root_inorder_index = node_to_inorder_index[preorder[preorder_start]];
    auto left_subtree_size = root_inorder_index - inorder_start;

    return std::make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
            preorder[preorder_start],
            BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1, preorder_start + 1 + left_subtree_size,
                                                inorder_start, root_inorder_index, node_to_inorder_index),
            BinaryTreeFromPreorderInorderHelper(preorder, preorder_start + 1 + left_subtree_size, preorder_end,
                                                root_inorder_index + 1, inorder_end, node_to_inorder_index)
    });
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
        const vector<int> &preorder, const vector<int> &inorder) {
    std::map<int, size_t> node_to_inorder_index;
    for (auto i = 0; i < inorder.size(); i++) {
        node_to_inorder_index.emplace(inorder[i], i);
    }
    return BinaryTreeFromPreorderInorderHelper
            (preorder, 0, preorder.size(), 0, inorder.size(), node_to_inorder_index);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
