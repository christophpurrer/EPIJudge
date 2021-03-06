#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int> &A, int m, const vector<int> &B, int n) {
    int wIndex = m + n - 1;
    if (wIndex >= A.size()) {
        throw std::invalid_argument("B can't be merged into A");
    }
    m--;
    n--;
    // Merge B into A
    while (m >= 0 && n >= 0) {
        A[wIndex--] = A[m] > B[n] ? A[m--] : B[n--];
    }
    // Merge rest of B
    while (n >= 0) {
        A[wIndex--] = B[n--];
    }
}

vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
