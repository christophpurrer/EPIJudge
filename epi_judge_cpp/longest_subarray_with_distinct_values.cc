#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int> &A) {
    std::unordered_map<int, int> pos;
    int result = 0;
    for (int left = 0, right = 0; right < A.size(); right++) {
        pos[A[right]]++;
        while (pos[A[right]] > 1) {
            pos[A[left]]--;
            left++;
        }
        result = std::max(result, right - left + 1);
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
