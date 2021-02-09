#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> ExamineBuildingsWithSunset(
        vector<int>::const_iterator sequence_begin,
        const vector<int>::const_iterator &sequence_end) {
    struct BuildingWithHeight {
        int id;
        int height;
    };
    std::stack<BuildingWithHeight> stack;
    int i = 0;
    while (sequence_begin != sequence_end) {
        int height = *sequence_begin;
        while (!stack.empty() &&stack.top().height <= height) {
            stack.pop();
        }
        stack.emplace(BuildingWithHeight{i, height});
        i++;
        sequence_begin++;
    }
    vector<int> result;
    while (!stack.empty()) {
        result.emplace_back(stack.top().id);
        stack.pop();
    }
    return result;
}

vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
