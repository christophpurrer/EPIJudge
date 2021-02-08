#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

void advanceN(shared_ptr<ListNode<int>> *l, int n) {
    while (n--) {
        *l = (*l)->next;
    }
}

int length(shared_ptr<ListNode<int>> *l) {
    int lSize = 1;
    auto lTail = l;
    while (*lTail && (*lTail)->next) {
        lSize++;
        *lTail = (*lTail)->next;
    }
    return lSize;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
        shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {

    auto l0Tail = l0;
    int l0Size = length(&l0Tail);
    auto l1Tail = l1;
    int l1Size = length(&l1Tail);

    // not overlapping?
    if (l0Tail != l1Tail) return nullptr;

    advanceN(l0Size > l1Size ? &l0 : &l1, std::abs(l0Size - l1Size));
    while (l0 && l1 && l0 != l1) {
        l0 = l0->next;
        l1 = l1->next;
    }
    return l0; // or L1;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
