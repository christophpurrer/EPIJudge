#include <set>
#include <vector>
#include <array>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void EvenOdd1(vector<int> *A_ptr) {
    auto l = 0;
    auto r = A_ptr->size() - 1;
    while (l < r) {
        if (A_ptr->at(l) % 2 == 0) {
            l++;
        } else if (A_ptr->at(r) % 2 != 0) {
            r--;
        } else {
            auto tmp = A_ptr->at(l);
            A_ptr->at(l) = A_ptr->at(r);
            A_ptr->at(r) = tmp;
            l++;
            r--;
        }
    }

    std::array<int, 3> A {1,2,3};

}

void EvenOdd(vector<int> *A_ptr) {
    vector<int>& A = *A_ptr;
    int l = 0, r = A.size() - 1;
    while (l < r) {
        if (A[l] % 2 == 0) {
            l++;
        } else if (A[r] % 2 != 0) {
            r--;
        } else {
            std::swap(A[l++], A[r--]);
        }
    }
}

void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
