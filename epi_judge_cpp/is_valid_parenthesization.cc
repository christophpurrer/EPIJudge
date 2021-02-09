#include <string>
#include <map>
#include "test_framework/generic_test.h"

using std::string;

bool IsWellFormed(const string &s) {
    std::stack<char> stack;
    std::map<char, char> map = {{')', '('},
                                {']', '['},
                                {'}', '{'}};
    for (char c: s) {
        // opening
        if (c == '(' || c == '[' || c == '{') {
            stack.emplace(c);
        } // closing
        else if (map.find(c) != map.end()) {
            if (stack.empty()) return false;
            auto value = stack.top();
            stack.pop();
            if (value != map.at(c)) return false;
        } else {
            return false;
        }
    }
    return stack.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
