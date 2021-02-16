#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
        const vector<string> &paragraph, const unordered_set<string> &keywords) {
    std::unordered_map<string, int> covered;
    Subarray result = {-1, -1};
    for (int start = 0, end = 0; end < paragraph.size(); end++) {
        if (keywords.count(paragraph[end])) {
            covered[paragraph[end]]++;
        }
        while (covered.size() == keywords.size()) {
            if (result.start == -1 && result.end == -1 || end - start < result.end - result.start) {
                result = {start, end};
            }
            if (keywords.count(paragraph[start])) {
                covered[paragraph[start]]--;
                if (covered[paragraph[start]] == 0) {
                    covered.erase(paragraph[start]);
                }
            }
            start++;
        }
    }
    return result;
}

Subarray FindSmallestSubarrayCoveringSetPoorer(
        const vector<string> &paragraph, const unordered_set<string> &keywords) {
    std::unordered_map<string, int> pos;
    int start = -1, end = -1;
    for (int i = 0; i < paragraph.size(); i++) {
        const auto &word = paragraph[i];
        if (keywords.find(word) != keywords.end()) {
            pos[word] = i;
        }
        if (pos.size() == keywords.size()) {
            int localStart = std::numeric_limits<int>::max(), localEnd = 0;
            for (auto const &entry : pos) {
                localStart = std::min(localStart, entry.second);
                localEnd = std::max(localEnd, entry.second);
            }
            if (start == -1 || (localEnd - localStart < end - start)) {
                start = localStart;
                end = localEnd;
            }
        }
    }
    return {start, end};
}

int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
