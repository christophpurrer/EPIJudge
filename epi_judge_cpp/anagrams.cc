#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string> &dictionary) {
    std::map<string, std::vector<string>> map;
    for (const auto &s : dictionary) {
        std::string sorted_s{s};
        std::sort(sorted_s.begin(), sorted_s.end());
        map[sorted_s].emplace_back(s);
    }

    std::vector<std::vector<string>> result;
    for (const auto &entry : map) {
        if (entry.second.size() > 1) {
            result.emplace_back(entry.second);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
