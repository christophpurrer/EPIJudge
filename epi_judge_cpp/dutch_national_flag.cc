#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kRed, kWhite, kBlue };

// First approach. O(1) space BUT O(n^2) time!!!
void DutchFlagPartition1(int pivot_index, vector<Color> *A_ptr) {
    vector<Color> &A = *A_ptr;
    Color pivot = A[pivot_index];
    // First pass: group elements smaller than the pivot
    for (auto i = 0; i < A.size(); i++) {
        for (auto j = i + 1; j < A.size(); j++) {
            if (A[j] < pivot) {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
    // Second pass: group elements larger than the pivot
    for (auto i = A.size() - 1; i >= 0 && A[i] >= pivot; i--) {
        // Look for larger element. Stop when we reached an element less than the pivot
        // First pass has already handled that
        for (auto j = i - 1; j >= 0 && A[j] >= pivot; --j) {
            if (A[j] > pivot) {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
    return;
}

// Second approach. O(1) space and O(n) time
void DutchFlagPartition2(int pivot_index, vector<Color> *A_ptr) {
    vector<Color> &A = *A_ptr;
    Color pivot = A[pivot_index];
    // First pass: group elements smaller than the pivot
    auto smaller = 0;
    for (auto i = 1; i < A.size(); i++) {
        if (A[i] < pivot) {
            std::swap(A[i], A[smaller++]);
        }
    }
    // Second pass: group elements larger than the pivot
    auto larger = A.size() - 1;
    for (auto i = A.size() - 2; i >= 0 && A[i] >= pivot; i--) {
        if (A[i] > pivot) {
            std::swap(A[i], A[larger--]);
        }
    }
}

void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
    vector<Color> &A = *A_ptr;
    Color pivot = A[pivot_index];
    /*
     * Keep the following invariants during partitioning
     * bottom group A[0 : smaller - 1]
     * middle group A[smaller : equal - 1]
     * unclassified group A[equal : larger - 1]
     * top group A[larger : A.size() - 1]
     */
    int smaller = 0, equal = 0, larger = A.size();
    while (equal < larger) {
        // A[equal] is the ine incoming unclassified element
        if (A[equal] < pivot) {
            std::swap(A[smaller++], A[equal++]);
        } else if (A[equal] == pivot) {
            equal++;
        } else { // A[equal] > pivot
            std::swap(A[equal], A[--larger]);
        }
    }
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
