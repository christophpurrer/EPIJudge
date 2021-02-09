#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
        const unique_ptr<BinaryTreeNode<int>> &tree) {
    std::vector<std::vector<int>> result;
    std::queue<BinaryTreeNode<int> *> queue;
    queue.emplace(tree.get());
    while (!queue.empty() && queue.front() != nullptr) {
        result.emplace_back(std::vector<int>());
        std::queue<BinaryTreeNode<int> *> next;
        while (!queue.empty()) {
            auto value = queue.front();
            result.back().emplace_back(value->data);
            queue.pop();
            if (value->left) {
                next.emplace(value->left.get());
            }
            if (value->right) {
                next.emplace(value->right.get());
            }
        }
        queue = next;
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
