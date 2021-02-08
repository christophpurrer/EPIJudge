#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>> &L) {
    auto E = L;
    auto O = E ? E->next : nullptr;
    while (E) {
        if (O) {
            E->next = O->next;
            if (E->next) {
                E = E->next;
                O->next = E->next;
                O = O->next;
            } else {}
            E->next = L;
        } else {
            E->next = L->next;
            E = nullptr;
        }
    }
    return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
