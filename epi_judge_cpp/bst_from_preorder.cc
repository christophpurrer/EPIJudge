#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

// Approach 1 O(n^2)
unique_ptr<BstNode<int>> RebuildBSTFromPreorderHelper(
        const vector<int> &preorder_sequence, int start, int end) {
    if (start >= end) return nullptr;

    int transitionPoint = start + 1;
    while (transitionPoint < end && preorder_sequence[transitionPoint] < preorder_sequence[start]) {
        transitionPoint++;
    }

    return std::make_unique<BstNode<int>>(preorder_sequence[start],
                                          RebuildBSTFromPreorderHelper(preorder_sequence, start + 1, transitionPoint),
                                          RebuildBSTFromPreorderHelper(preorder_sequence, transitionPoint, end));
}

// Approach 2 O(n)
unique_ptr<BstNode<int>>
RebuildBSTFromPreorderFaster(const vector<int> &preorder_sequence, int lowerBound, int upperBound, int *rootIndexPtr) {
    if (*rootIndexPtr >= preorder_sequence.size()) return nullptr;

    int root = preorder_sequence[*rootIndexPtr];
    if (root < lowerBound || root > upperBound) return nullptr;
    (*rootIndexPtr)++;

    auto left = RebuildBSTFromPreorderFaster(preorder_sequence, lowerBound, root, rootIndexPtr);
    auto right = RebuildBSTFromPreorderFaster(preorder_sequence, root, upperBound, rootIndexPtr);
    return std::make_unique<BstNode<int>>(root, std::move(left), std::move(right));
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
        const vector<int> &preorder_sequence) {
    auto A = RebuildBSTFromPreorderHelper(preorder_sequence, 0, preorder_sequence.size());
    int rootIndex = 0;
    auto B = RebuildBSTFromPreorderFaster(preorder_sequence, std::numeric_limits<int>::min(),
                                          std::numeric_limits<int>::max(), &rootIndex);
    return B;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
