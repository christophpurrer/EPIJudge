#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> SortApproximatelySortedData(
        vector<int>::const_iterator sequence_begin,
        const vector<int>::const_iterator &sequence_end, int k) {
    std::priority_queue<int, vector<int>, std::greater<>> minHeap;
    std::vector<int> result;

    for (int i = 0; sequence_begin != sequence_end; i++, sequence_begin++) {
        minHeap.emplace(*sequence_begin);
        if (i >= k) {
            result.emplace_back(minHeap.top());
            minHeap.pop();
        }
    }

    while (!minHeap.empty()) {
        result.emplace_back(minHeap.top());
        minHeap.pop();
    }
    return result;
}

vector<int> SortApproximatelySortedDataWrapper(const vector<int> &sequence,
                                               int k) {
    return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
