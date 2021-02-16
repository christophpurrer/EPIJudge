#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int> &A,
                                     const vector<int> &B) {
    std::vector<int> result;
    auto iterA = A.begin();
    auto iterB = B.begin();
    while (iterA != A.end() && iterB != B.end()) {
        if (*iterA < *iterB) {
            iterA++;
        } else if (*iterA == *iterB) {
            if (result.empty() || result.back() != *iterA) {
                result.emplace_back(*iterA);
            }
            iterA++;
            iterB++;
        } else {
            iterB++;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
