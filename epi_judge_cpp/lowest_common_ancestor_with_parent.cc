#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int getDepth(BinaryTreeNode<int> *node) {
    int depth = 0;
    while (node) {
        depth++;
        node = node->parent;
    }
    return depth;
}

BinaryTreeNode<int> *Lca(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1) {
    auto *iter0 = node0.get(), *iter1 = node1.get();
    auto depth0 = getDepth(iter0), depth1 = getDepth(iter1);

    if (depth1 > depth0) {
        std::swap(iter1, iter0);
    }

    auto depthDiff = std::abs(depth1 - depth0);
    while (depthDiff) {
        iter0 = iter0->parent;
        depthDiff--;
    }

    while (iter0 != iter1) {
        iter0 = iter0->parent;
        iter1 = iter1->parent;
    }
    return iter0;
}

BinaryTreeNode<int> *LcaSpacious(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1) {

    std::stack<BinaryTreeNode<int> *> node0Path;
    {
        auto node0iter = node0.get();
        while (node0iter) {
            node0Path.emplace(node0iter);
            node0iter = node0iter->parent;
        }
    }
    std::stack<BinaryTreeNode<int> *> node1Path;
    {
        auto node1iter = node1.get();
        while (node1iter) {
            node1Path.emplace(node1iter);
            node1iter = node1iter->parent;
        }
    }

    BinaryTreeNode<int> *result = nullptr;
    while (!node0Path.empty() && !node1Path.empty() && node0Path.top() == node1Path.top()) {
        result = node0Path.top();
        node0Path.pop();
        node1Path.pop();
    }
    return result;
}

int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
