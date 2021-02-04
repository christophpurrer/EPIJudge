#include "test_framework/generic_test.h"
#include <algorithm>
#include <string>

// ## Approach 1 > Use string
long long Reverse1(int x) {
    auto sign = x < 0 ? -1 : 1;
    auto s = std::to_string(abs(x));
    std::reverse(s.begin(), s.end());
    return std::stoll(s) * sign;
}

long long Reverse(int x) {
    auto sign = x < 0 ? -1 : 1;
    x = abs(x);
    long long result = 0;
    while (x > 0) {
        result *= 10;
        result += x % 10;
        x /= 10;
    }
    return result * sign;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
