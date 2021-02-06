#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void ApplyPermutationWithNSpace(vector<int> perm, vector<int> *A_ptr) {
    vector<int> result(A_ptr->size(), 0);
    for (int i = 0; i < perm.size(); i++) {
        result[perm[i]] = A_ptr->at(i);
    }
    for (int i = 0; i < result.size(); i++) {
        A_ptr->at(i) = result[i];
    }
}

void ApplyPermutation(vector<int> perm, vector<int> *A_ptr) {
    for (int i = 0; i < A_ptr->size(); i++) {
        int next = i;
        while (perm.at(next) >= 0) {
            std::swap(A_ptr->at(i), A_ptr->at(perm[next]));
            int temp = perm[next];
            perm[next] -= perm.size();
            next = temp;
        }
    }
    std::for_each(perm.begin(), perm.end(), [&perm](int &x) { x += perm.size(); });
}

vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
