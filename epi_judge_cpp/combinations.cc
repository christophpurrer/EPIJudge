#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void CombinationsHelper(int n, int k, int i, std::vector<int> &partial, std::vector<std::vector<int>> &result) {
    // Base case
    if (partial.size() == k) {
        result.emplace_back(partial);
        return;
    }

    // Recursive case(s)
//    const int remaining = k - partial.size();
//    for (int j = i; j <= n && remaining <= n - j + 1; j++) {
//        // Take element at i
//        partial.emplace_back(j);
//        CombinationsHelper(n, k, j + 1, partial, result);
//        partial.pop_back();
//    }

    // Take element at i
    if (i <= n) {
        partial.emplace_back(i);
        CombinationsHelper(n, k, i + 1, partial, result);
        partial.pop_back();
        CombinationsHelper(n, k, i + 1, partial, result);
    }
}

vector<vector<int>> Combinations(int n, int k) {
    std::vector<std::vector<int>> result;
    std::vector<int> partial;
    CombinationsHelper(n, k, 1, partial, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}
