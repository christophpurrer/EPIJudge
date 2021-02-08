#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> MergeTwoSortedListsMine(shared_ptr<ListNode<int>> L1,
                                                  shared_ptr<ListNode<int>> L2) {
    auto head = std::make_shared<ListNode<int>>(-1);
    auto curNode = head;
    while (L1 || L2) {
        if (L1 && !L2 || L1 && L1->data < L2->data) {
            curNode->next = L1;
            L1 = L1->next;
        } else {
            curNode->next = L2;
            L2 = L2->next;
        }
        curNode = curNode->next;
    }
    return head->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
    auto head = std::make_shared<ListNode<int>>(-1);
    auto curNode = head;
    while (L1 && L2) {
        if (L1->data < L2->data) {
            curNode->next = L1;
            L1 = L1->next;
        } else {
            curNode->next = L2;
            L2 = L2->next;
        }
        curNode = curNode->next;
    }
    curNode->next = L1 ? L1 : L2;
    return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
