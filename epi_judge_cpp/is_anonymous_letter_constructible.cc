#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;


bool IsLetterConstructibleFromMagazine(const string &letter_text,
                                       const string &magazine_text) {
    std::unordered_map<char, int> map;
    for (const auto &c : letter_text) {
        map[c]++;
    }

    for (const auto &c : magazine_text) {
        if (map[c] > 0) {
            map[c]--;
        }
        if (map[c] == 0) {
            map.erase(c);
        }
    }

    return map.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
