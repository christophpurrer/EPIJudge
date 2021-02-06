#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int> &A) {
    int maxSubArray = 1;
    int curSubArray = 1;
    for (int i = 1; i < A.size(); i++) {
        if (A[i] == A[i - 1]) {
            curSubArray++;
            maxSubArray = std::max(maxSubArray, curSubArray);
        } else {
            curSubArray = 1;
        }
    }
    return maxSubArray;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
