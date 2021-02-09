#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
BinaryTreeNode<int> *FindSuccessor(
        const unique_ptr<BinaryTreeNode<int>> &node) {
    if (!node) return nullptr;
    auto *iter = node.get();

    // 1.) successor in the right sub tree
    if (iter->right) {
        iter = iter->right.get();
        while (iter->left) {
            iter = iter->left.get();
        }
        return iter;
    }

    // 2.) walk up parents until we aren't a right child anymore
    while (iter->parent && iter->parent->right.get() == iter) {
        iter = iter->parent;
    }

    // 3.) successor is the parent
    return iter->parent;
}

int FindSuccessorWrapper(const unique_ptr<BinaryTreeNode<int>>& tree,
                         int node_idx) {
  auto result = FindSuccessor(MustFindNode(tree, node_idx));
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "node_idx"};
  return GenericTestMain(args, "successor_in_tree.cc", "successor_in_tree.tsv",
                         &FindSuccessorWrapper, DefaultComparator{},
                         param_names);
}
