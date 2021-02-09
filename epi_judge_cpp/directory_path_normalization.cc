#include <string>
#include <sstream>

#include "test_framework/generic_test.h"

using std::string;

string ShortestEquivalentPath(const string &path) {
    std::stringstream ss(path);
    const char delimiter = '/';
    std::string segment;
    std::vector<string> stack;

    while (getline(ss, segment, delimiter)) {
        if (segment.length() > 0) {
            if (segment == "..") {
                if (stack.empty() || stack.back() == "..") {
                    stack.emplace_back(segment);
                } else {
                    stack.pop_back();
                }
            } else if (segment != ".") {
                stack.emplace_back(segment);
            }
        }
    }
    std::string result{path.front() == '/' ? "/" : ""};
    for (auto dir: stack) {
        if (result.size() > 1) result += "/";
        result += dir;
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
