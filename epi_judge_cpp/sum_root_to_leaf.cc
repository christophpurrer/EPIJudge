#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

void SumRootToLeafHelper1(BinaryTreeNode<int> *node, std::string sumSoFar, std::vector<std::string> &sums) {
    sumSoFar += std::to_string(node->data);
    if (!node->left && !node->right) {
        sums.emplace_back(sumSoFar);
    }
    if (node->left) {
        SumRootToLeafHelper1(node->left.get(), sumSoFar, sums);
    }
    if (node->right) {
        SumRootToLeafHelper1(node->right.get(), sumSoFar, sums);
    }
}

int BinaryToDecimal(std::string binary) {
    std::reverse(binary.begin(), binary.end());
    int result = 0;
    int base = 0;
    for (char c: binary) {
        result += (c - '0') * pow(2, base);
        base++;
    }
    return result;
}

int SumRootToLeaf1(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (!tree) return 0;
    std::vector<std::string> sums;
    SumRootToLeafHelper1(tree.get(), "", sums);
    int result = 0;
    for (auto sum : sums) {
        result += BinaryToDecimal(sum);
    }
    return result;
}

void SumRootToLeafHelper2(BinaryTreeNode<int> *node, int sumSoFar, std::vector<int> &sums) {
    sumSoFar *= 2;
    sumSoFar += node->data;
    if (!node->left && !node->right) {
        sums.emplace_back(sumSoFar);
    }
    if (node->left) {
        SumRootToLeafHelper2(node->left.get(), sumSoFar, sums);
    }
    if (node->right) {
        SumRootToLeafHelper2(node->right.get(), sumSoFar, sums);
    }
}

int SumRootToLeaf2(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (!tree) return 0;
    std::vector<int> sums;
    SumRootToLeafHelper2(tree.get(), 0, sums);
    int result = 0;
    for (auto sum : sums) {
        result += sum;
    }
    return result;
}

int SumRootToLeafHelper(BinaryTreeNode<int> *node, int sumSoFar) {
    if (!node) return 0;
    sumSoFar *= 2;
    sumSoFar += node->data;
    if (!node->left && !node->right) {
        return sumSoFar;
    }
    return SumRootToLeafHelper(node->left.get(), sumSoFar) + SumRootToLeafHelper(node->right.get(), sumSoFar);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>> &tree) {
    if (!tree) return 0;
    return SumRootToLeafHelper(tree.get(), 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
