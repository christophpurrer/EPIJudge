#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end) {
    std::priority_queue<int, vector<int>, std::greater<>> minHeap;
    // std::priority_queue<int, vector<int>, std::less<>> maxHeap;
    std::priority_queue<int, vector<int>> maxHeap;

    vector<double> result;
    double value;
    for (; sequence_begin != sequence_end; sequence_begin++) {
        value = *sequence_begin;
        if (minHeap.empty()) {
            minHeap.emplace(value);
        } else {
            if (value >= minHeap.top()) {
                minHeap.emplace(value);
            } else {
                maxHeap.emplace(value);
            }
        }

        if (minHeap.size() > maxHeap.size() + 1) {
            maxHeap.emplace(minHeap.top());
            minHeap.pop();
        } else if (maxHeap.size() > minHeap.size()) {
            minHeap.emplace(maxHeap.top());
            maxHeap.pop();
        }

        result.emplace_back(minHeap.size() == maxHeap.size() ? 0.5 * (minHeap.top() + maxHeap.top()) : minHeap.top());
    }
    return result;
}

vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
