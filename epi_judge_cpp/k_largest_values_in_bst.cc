#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void FindKLargestInBSTHelper(BstNode<int> *node, int k, std::vector<int> &result) {
    if (!node) return;
    // go right
    FindKLargestInBSTHelper(node->right.get(), k, result);
    // visit
    if (result.size() == k) return;
    result.emplace_back(node->data);
    // go left
    FindKLargestInBSTHelper(node->left.get(), k, result);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>> &tree, int k) {
    std::vector<int> result;
    FindKLargestInBSTHelper(tree.get(), k, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
