#include <string>

#include "test_framework/generic_test.h"

using std::string;

string ConvertBase(const string &num_as_string, int b1, int b2) { // from base2 to base16
    // handle sign
    const bool is_negative = num_as_string.size() > 0 && num_as_string.front() == '-';

    // from string in b1 to number in base10
    long value = 0;
    for (int i = is_negative ? 1 : 0; i < num_as_string.size(); i++) {
        value *= b1;
        value += isdigit(num_as_string[i]) ? num_as_string[i] - '0' : num_as_string[i] - 'A' + 10;
    }
    // Handle 0 case
    if (value == 0) return "0";

    // from number in base10 to string in b2
    std::string result;
    while (value) {
        int reminder = value % b2;
        result += reminder >= 10 ? 'A' + reminder - 10 : '0' + reminder;
        value /= b2;
    }
    if (is_negative) {
        result += '-';
    }
    return {result.rbegin(), result.rend()};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
