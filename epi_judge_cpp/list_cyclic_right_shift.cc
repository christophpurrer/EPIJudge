#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
    if (k == 0) return L;

    auto node = L;
    shared_ptr<ListNode<int>> prev = nullptr;
    while (k-- > 0) {
        prev = node;
        node = node->next;
    }

    auto result = node;
    if (prev) {
        prev->next = nullptr;
    }

    while (node->next) {
        node = node->next;
    }
    node->next = L;
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
