#include "test_framework/generic_test.h"
#include <iostream>

double SquareRoot(double x) {
    std::cout << "std::numeric_limits<double>::epsilon(): " << std::numeric_limits<double>::epsilon() << std::endl;

    double left, right;
    if (x < 1.0) {
        left = x, right = 1.0;
    } else {
        left = 1.0, right = x;
    }
    while (std::abs(right - left) / left > std::numeric_limits<double>::epsilon()) {
        double mid = left + (right - left) / 2;
        double mid_squared = mid * mid;
        if (mid_squared == x) {
            return mid;
        } else if (mid_squared > x) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left; // || right ;-)
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
