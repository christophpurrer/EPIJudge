#include "test_framework/generic_test.h"
#include <string>

// ## Approach 1 using string
bool IsPalindromeNumber1(int x) {
    if (x < 0) return false;
    auto s = std::to_string(x);
    auto l = 0;
    auto r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

bool IsPalindromeNumber(int x) {
    if (x < 0) return false;

    auto num_digits = static_cast<int>( floor(log10(x)) + 1);
    auto msd_mask = static_cast<int>(pow(10, num_digits - 1));
    for (auto i = 0; i < (num_digits / 2); i++) {
        if (x / msd_mask != x % 10) return false;
        x %= msd_mask;
        x /= 10;
        msd_mask /= 100;
    }
    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
