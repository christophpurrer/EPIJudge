#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void PermutationsHelper(int n, std::vector<int> &A,
                        std::vector<std::vector<int>> &result) {
    if (n == A.size() - 1) {
        result.emplace_back(A);
        return;
    }

    for (int j = n; j < A.size(); j++) {
        std::swap(A[n], A[j]);
        PermutationsHelper(n + 1, A, result);
        std::swap(A[j], A[n]);
    }
}

vector<vector<int>> Permutations(vector<int> A) {
    std::vector<std::vector<int>> result;
    PermutationsHelper(0, A, result);
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A"};
    return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                           &Permutations, UnorderedComparator{}, param_names);
}

