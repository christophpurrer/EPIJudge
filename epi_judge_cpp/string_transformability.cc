#include <string>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

int TransformString(unordered_set<string> D, const string &s, const string &t) {
    std::queue<std::pair<std::string, int>> q;
    D.erase(s);
    // string value : distance
    q.emplace(std::pair<std::string, int>{s, 0});
    // Look for t
    while (!q.empty()) {
        auto val = q.front();
        q.pop();
        if (val.first == t) return val.second;

        // Try out all transformations
        std::string str = val.first;
        for (int i = 0; i < val.first.size(); i++) {
            for (int j = 0; j < 26; j++) {
                str[i] = 'a' + j;
                if (auto it = D.find(str) != D.end()) {
                    D.erase(str);
                    q.emplace(std::pair<std::string, int>{str, val.second + 1});
                }
            }
            str = val.first;
        }
    }

    // Not found
    return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
