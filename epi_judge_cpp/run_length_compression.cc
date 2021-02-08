#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"

using std::string;

string Decoding(const string &s) {
    std::string result;
    int count = 0;
    for (const char &c : s) {
        if (isdigit(c)) {
            count *= 10;
            count += c - '0';
        } else {
            result += std::string(count, c);
            count = 0;
        }
    }
    return result;
}

string Encoding(const string &s) {
    std::string result;
    int count = 1;
    for (int i = 1; i <= s.size(); i++) {
        if (s[i] == s[i - 1] && i < s.size()) {
            count++;
        } else {
            result += std::to_string(count) + s[i - 1];
            count = 1;
        }
    }
    return result;
}

void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
