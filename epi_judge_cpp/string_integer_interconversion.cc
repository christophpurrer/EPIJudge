#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

std::string IntToString(int x) {
    const bool is_negative = x < 0; // get sign
    std::string s;
    do {
        s += '0' + std::abs(x % 10); // avoid int overflow
        x /= 10;
    } while (x);
    if (is_negative) {
        s += '-';
    }
    return {s.rbegin(), s.rend()}; // reverse string
}

int StringToInt(const string &s) {
    int result = 0;
    const bool hasSign = s.size() > 0 && (s[0] == '-' || s[0] == '+');
    for (int i = hasSign ? 1 : 0; i < s.size(); i++) {
        result *= 10;
        result += s[i] - '0';
    }
    return s.size() > 0 && s[0] == '-' ? -result : result;
}

bool isPalindromic(const std::string &s) {
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
