#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool isPalindrome(const std::string &text, int left, int right) {
    while (left < right) {
        if (text[left++] != text[right--])return false;
//        left++;
//        right--;
    }
    return true;
}

void PalindromeDecompositionsHelper(const string &text, int n, std::vector<std::string> partial,
                                    std::vector<std::vector<std::string>> &result) {
    // Base case: solution found
    if (n == text.size()) {
        result.emplace_back(partial);
        return;
    }

    // Recursive case
    for (int i = n; i < text.size(); i++) {
        if (isPalindrome(text, n, i)) {
            partial.emplace_back(text.substr(n, i - n + 1));
            PalindromeDecompositionsHelper(text, i + 1, partial, result);
            partial.pop_back();
        }
    }
}

vector<vector<string>> PalindromeDecompositions(const string& text) {
    std::vector<std::vector<std::string>> result;
    std::vector<string> partial;
    PalindromeDecompositionsHelper(text,0, partial, result);
    return result;
}
bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"text"};
  return GenericTestMain(args, "enumerate_palindromic_decompositions.cc",
                         "enumerate_palindromic_decompositions.tsv",
                         &PalindromeDecompositions, &Comp, param_names);
}
