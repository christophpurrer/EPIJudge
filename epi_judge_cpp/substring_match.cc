#include <string>

#include "test_framework/generic_test.h"

using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
    if (s.size() > t.size()) return -1; // s is not a substring of t

    const int kBase = 26;
    int t_hash = 0, s_hash = 0;
    int power_s = 1;
    for (int i = 0; i < s.size(); i++) {
        if (i > 0) {
            power_s *= kBase;
        }
        t_hash = t_hash * kBase + t[i];
        s_hash = s_hash * kBase + s[i];
    }

    for (int i = s.size(); i <= t.size(); i++) {
        if (t_hash == s_hash && t.compare(i - s.size(), s.size(), s) == 0) {
            return i - s.size();
        }

        // Rolling hash
        if (i < t.size()) {
            t_hash -= t[i - s.size()] * power_s;
            t_hash = t_hash * kBase + t[i];
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
