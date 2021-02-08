#include <string>
#include <vector>

#include "test_framework/generic_test.h"

using std::string;
using std::vector;

const std::array<std::string, 10> kMapping = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

void PhoneMnemonicRec(const string &phone_number_remain, const string &mnenomic, vector<string> &result) {
    // base case
    if (phone_number_remain.empty()) {
        result.emplace_back(mnenomic);
    } else {
        // recursive case
        int digit = phone_number_remain[0] - '0';
        for (char c: kMapping[digit]) {
            PhoneMnemonicRec(phone_number_remain.substr(1), mnenomic + c, result);
        }
    }
}

vector<string> PhoneMnemonic(const string &phone_number) {
    vector<string> result;
    PhoneMnemonicRec(phone_number, "", result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
