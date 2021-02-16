#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string> &paragraph) {
    int result = std::numeric_limits<int>::max();
    std::unordered_map<std::string, int> pos;
    for (int i = 0; i < paragraph.size(); i++) {
        auto const &word = paragraph[i];
        auto it = pos.find(word);
        if (it != pos.end()) {
            result = std::min(result, i - it->second);
        }
        pos[word] = i;
    }
    return result != std::numeric_limits<int>::max() ? result :
           -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
