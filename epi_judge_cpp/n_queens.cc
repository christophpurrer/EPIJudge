#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

bool isValid(std::vector<int> &partial) {
    int rowId = partial.size() - 1;
    for (int i = 0; i < rowId; i++) {
        int diff = std::abs(partial[i] - partial[rowId]);
        if (diff == 0 || diff == rowId - i) return false;
    }
    return true;
}

void SolveNQueens(int n, int row, std::vector<int>& partial, std::vector<std::vector<int>> &result) {
    // Base case
    if (row == n) {
        result.emplace_back(partial);
        return;
    }

    // Recursive case
    for (int c = 0; c < n; c++) {
        partial.emplace_back(c);
        if (isValid(partial)) {
            SolveNQueens(n, row + 1, partial, result);
        }
        partial.pop_back();
    }
}

vector<vector<int>> NQueens(int n) {
    std::vector<std::vector<int>> result;
    std::vector<int> partial;
    SolveNQueens(n, 0, partial, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
