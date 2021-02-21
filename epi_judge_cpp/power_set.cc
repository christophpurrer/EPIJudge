#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

void GeneratePowerSetHelper(const vector<int> &input_set, int i, std::vector<int> &partial,
                            std::vector<std::vector<int>> &result) {

    // Base case
    if (i == input_set.size()) {
        result.emplace_back(partial);
        return;
    }

    // Recursive case(1)
    // A.) don't include value
    GeneratePowerSetHelper(input_set, i + 1, partial, result);

    // B.) include value
    partial.emplace_back(input_set[i]);
    GeneratePowerSetHelper(input_set, i + 1, partial, result);
    partial.pop_back();
}

vector<vector<int>> GeneratePowerSet(const vector<int> &input_set) {
    std::vector<std::vector<int>> result;
    std::vector<int> partial;
    GeneratePowerSetHelper(input_set, 0, partial, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
