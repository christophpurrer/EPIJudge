#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
    const int sign = num1.front() < 0 ^ num2.front() < 0 ? -1 : 1;
    num1.front() = abs(num1.front());
    num2[0] = abs(num2[0]); // Alternative num2.front() = abs(num2.front());

    vector<int> result(num1.size() + num2.size(), 0);
    // Grad school multiply
    for (int i = num1.size() - 1; i >= 0; i--) {
        for (int j = num2.size() - 1; j >= 0; j--) {
            result[i + j + 1] += num1[i] * num2[j];
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    // Remove leading zero: Option A
//    while (result.size() > 0 && result[0] == 0) {
//        result.erase(result.begin());
//    }

    // Remove leading zero: Alternative
    auto firstZeros = 0;
    for (auto val : result) {
        if (val != 0) break;
        firstZeros++;
    }
    result = std::vector<int>(result.begin() + firstZeros, result.end());

    // Handle empty case
    if (result.empty()) { return {0}; }

    result.front() *= sign; // result[0] *= sign;
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
