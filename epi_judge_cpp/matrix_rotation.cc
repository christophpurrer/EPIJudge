#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void RotateMatrix(vector<vector<int>> *square_matrix_ptr) {
    vector<vector<int>> &matrix = *square_matrix_ptr;
    const int size = square_matrix_ptr->size() - 1;
    for (int i = 0; i < (square_matrix_ptr->size() / 2); i++) {
        for (int j = i; j < size - 1; j++) {
            // 4 way exchange
            int temp1 = matrix[size - j][i];
            int temp2 = matrix[size - i][size - j];
            int temp3 = matrix[j][size - i];
            int temp4 = matrix[i][j];
            matrix[i][j] = temp1;
            matrix[size - j][i] = temp2;
            matrix[size - i][size - j] = temp3;
            matrix[j][size - i] = temp4;
        }
    }
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
