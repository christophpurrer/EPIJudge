#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> MatrixInSpiralOrder(const vector<vector<int>> &square_matrix) {
    int left = 0;
    int top = 0;
    int right = square_matrix.size() - 1;
    int bottom = square_matrix.size() - 1;
    vector<int> result;
    while (left <= right || top <= bottom) {
        // Go right
        for (int i = left; i <= right; i++) {
            result.push_back(square_matrix[top][i]);
        }
        top++;
        // Go down
        for (int i = top; i <= bottom; i++) {
            result.push_back(square_matrix[i][right]);
        }
        right--;
        // Go left
        for (int i = right; i >= left; i--) {
            result.push_back(square_matrix[bottom][i]);
        }
        bottom--;
        // Go up
        for (int i = bottom; i >= top; i--) {
            result.push_back(square_matrix[i][left]);
        }
        left++;
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
