#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>> &partial_assignment) {
    // Check rows
    for (auto r = 0; r < 9; r++) {
        std::set<int> values;
        for (auto c = 0; c < 9; c++) {
            if (partial_assignment[r][c] > 0 && values.find(partial_assignment[r][c]) != values.end()) {
                return false;
            }
            values.insert(partial_assignment[r][c]);
        }
    }

    // Check cols
    for (auto c = 0; c < 9; c++) {
        std::set<int> values;
        for (auto r = 0; r < 9; r++) {
            if (partial_assignment[r][c] > 0 && values.find(partial_assignment[r][c]) != values.end()) {
                return false;
            }
            values.insert(partial_assignment[r][c]);
        }
    }

    // Check 3x3 sub arrays
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::set<int> values;
            for (auto r = 0; r < 3; r++) {
                for (auto c = 0; c < 3; c++) {
                    auto value = partial_assignment[i * 3 + r][j * 3 + c];
                    if (value > 0 && values.find(value) != values.end()) {
                        return false;
                    }
                    values.insert(value);
                }
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
