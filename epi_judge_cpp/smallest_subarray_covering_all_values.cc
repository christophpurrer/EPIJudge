#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
        const vector<string> &paragraph, const vector<string> &keywords) {
    std::unordered_map<string, int> keyword2Index;
    for (int i = 0; i < keywords.size(); i++) {
        keyword2Index[keywords[i]] = i;
    }
    std::vector<int> latestOccurence(keywords.size(), -1);
    std::vector<int> shortestSubarraylength(keywords.size(), std::numeric_limits<int>::max());
    Subarray result = {-1, -1};
    int shortestDistance = std::numeric_limits<int>::max();
    for (int i = 0; i < paragraph.size(); i++) {
        if (keyword2Index.count(paragraph[i])) {
            int index = keyword2Index[paragraph[i]];
            if (index == 0) {
                shortestSubarraylength[index] = 1;
            } else if (shortestSubarraylength[index - 1] != std::numeric_limits<int>::max()) {
                int distance = i - latestOccurence[index - 1];
                shortestSubarraylength[index] = distance + shortestSubarraylength[index - 1];
            }
            latestOccurence[index] = i;

            if (index == keywords.size() - 1 && shortestSubarraylength.back() < shortestDistance) {
                shortestDistance = shortestSubarraylength.back();
                result = {i - shortestSubarraylength.back() + 1, i};
            }
        }
    }
    return result;
}

int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor& executor, const vector<string>& paragraph,
    const vector<string>& keywords) {
  auto result = executor.Run([&] {
    return FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  });

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
