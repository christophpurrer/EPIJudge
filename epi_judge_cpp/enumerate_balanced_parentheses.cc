#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void
GenerateBalancedParenthesesHelper(int leftNeeded, int rightNeeded, std::string partial, std::vector<string> &result) {
    if (leftNeeded == 0 && rightNeeded == 0) {
        result.emplace_back(partial);
        return;
    }

    if (leftNeeded > 0) {
        GenerateBalancedParenthesesHelper(leftNeeded - 1, rightNeeded, partial + "(", result);
    }
    if (leftNeeded < rightNeeded) {
        GenerateBalancedParenthesesHelper(leftNeeded, rightNeeded - 1, partial + ")", result);
    }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
    std::vector<string> result;
    GenerateBalancedParenthesesHelper(num_pairs, num_pairs, "", result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
