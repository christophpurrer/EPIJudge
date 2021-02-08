#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool isValidPart(const string &s) {
    if (s.size() > 3) return false;
    if (s.front() == '0' && s.size() > 1) return false;
    int val = std::stoi(s);
    return val >= 0 && val <= 255;
}

vector<string> GetValidIpAddress(const string &s) {
    vector<string> result;
    // Loop 1st part
    for (int i = 1; i < s.size() && i < 4; i++) {
        const string first = s.substr(0, i);
        if (isValidPart(first)) {
            // Loop 2nd part
            for (int j = 1; i + j < s.size() && j < 4; j++) {
                const string second = s.substr(i, j);
                if (isValidPart(second)) {
                    // Loop 3rd part
                    for (int k = 1; i + j + k < s.size() && k < 4; k++) {
                        const string third = s.substr(i + j, k);
                        const string forth = s.substr(i + j + k);
                        if (isValidPart(third) && isValidPart(forth)) {
                            result.emplace_back(first + "." + second + "." + third + "." + forth);
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
