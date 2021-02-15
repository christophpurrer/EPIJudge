#include "test_framework/generic_test.h"

int SquareRoot(int k) {
    int left = 0, right = k / 2 + 1;
    int result = -1;
    while (left <= right) {
        long mid = left + (right - left) / 2;
        long squared = mid * mid;
        if (squared > k) {
            right = mid - 1;
        } else {
            result = mid;
            left = mid + 1;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
