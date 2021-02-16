#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

int LongestContainedRange(const vector<int> &A) {
    std::unordered_set<int> unprocessed(A.begin(), A.end());
    int maxInterval = 0;
    while (!unprocessed.empty()) {
        int value = *unprocessed.begin();
        unprocessed.erase(value);
        int lowerBound = value - 1;
        while (unprocessed.count(lowerBound)) {
            unprocessed.erase(lowerBound);
            lowerBound--;
        }
        int upperBound = value + 1;
        while (unprocessed.count(upperBound)) {
            unprocessed.erase(upperBound);
            upperBound++;
        }
        maxInterval = std::max(maxInterval, upperBound - lowerBound - 1);
    }
    return maxInterval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
