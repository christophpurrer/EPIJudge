#include <vector>
#include "test_framework/generic_test.h"

using std::vector;

bool CanReachEnd(const vector<int> &max_advance_steps) {
    int maxSoFar = 0;
// Book Solution
//    for (int i = 0; i <= maxSoFar && maxSoFar < max_advance_steps.size(); i++) {
//        maxSoFar = std::max(maxSoFar, i + max_advance_steps[i]);
//    }
//    return maxSoFar >= max_advance_steps.size() - 1;

    int l = 0, r = max_advance_steps.size() - 1;
    while (l < r && l <= maxSoFar) {
        maxSoFar = std::max(maxSoFar, l + max_advance_steps[l]);
        l++;
    }
    return maxSoFar >= r;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
