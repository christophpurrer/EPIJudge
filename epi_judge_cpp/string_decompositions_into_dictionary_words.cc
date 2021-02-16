#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"


using std::string;
using std::vector;

bool
HasAllWords(const std::string &s, std::unordered_map<string, int> wordCount, int start, int numWords,
            const int unitSize) {
    for (int i = 0; i < numWords; i++) {
        std::string curWord = s.substr(start + i * unitSize, unitSize);
        if (wordCount.find(curWord) == wordCount.end()) { return false; };

        wordCount[curWord]--;
        if (wordCount[curWord] == 0) { wordCount.erase(curWord); };
    }
    return true;
}


vector<int> FindAllSubstrings(const string &s, const vector<string> &words) {
    std::unordered_map<string, int> wordCount;
    for (const auto &w: words) {
        wordCount[w]++;
    }

    std::vector<int> result;
    const int unitSize = words.front().size();
    for (int i = 0; i + words.size() * unitSize <= s.size(); i++) {
        if (HasAllWords(s, wordCount, i, words.size(), unitSize)) {
            result.emplace_back(i);
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
