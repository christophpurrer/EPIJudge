#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    if (start == finish) return L;

    auto dummy_head = std::make_shared<ListNode<int>>(ListNode<int>{0, L});
    auto prevNode = dummy_head;
    for (int i = 1; i < start; i++) {
        prevNode = prevNode->next;
    }

    auto curNode = prevNode->next;
    while (start < finish) {
        auto temp = curNode->next;
        curNode->next = temp->next;
        temp->next = prevNode->next;
        prevNode->next = temp;
    }
    return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
