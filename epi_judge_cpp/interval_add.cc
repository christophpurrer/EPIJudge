#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval {
  int left, right;
};

vector<Interval> AddInterval(const vector<Interval> &disjoint_intervals,
                             Interval new_interval) {
    std::vector<Interval> result;
    int i = 0;
    // Existing intervals BEFORE new_interval
    while (i < disjoint_intervals.size() && disjoint_intervals[i].right < new_interval.left) {
        result.emplace_back(disjoint_intervals[i]);
        i++;
    }

    // Existing intervals WITHIN new_interval
    while (i < disjoint_intervals.size() && new_interval.right >= disjoint_intervals[i].left) {
        new_interval = {
                std::min(new_interval.left, disjoint_intervals[i].left),
                std::max(new_interval.right, disjoint_intervals[i].right),
        };
        i++;
    }
    result.emplace_back(new_interval);

    // Existing intervals AFTER new_interval
    while (i < disjoint_intervals.size()) {
        result.emplace_back(disjoint_intervals[i]);
        i++;
    }
    return result;
}

vector<Interval> AddIntervalSlower(const vector<Interval> &disjoint_intervals,
                             Interval new_interval) {
    std::vector<Interval> result;
    int newLeft = new_interval.left;
    int newRight = new_interval.right;
    for (const auto &interval: disjoint_intervals) {
        if (interval.right < new_interval.left || interval.left > new_interval.right) {
            result.emplace_back(interval);
        } else {
            newLeft = std::min(newLeft, interval.left);
            newRight = std::max(newRight, interval.right);
        }
    }
    result.emplace_back(Interval{newLeft, newRight});
    std::sort(result.begin(), result.end(),
              [](const Interval &left, const Interval &right) { return left.left < right.left; });
    return result;
}

namespace test_framework {
template <>
struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("length({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Interval& x) {
    return {x.right - x.left};
  }
};
}  // namespace test_framework
bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return PrintTo(out, std::make_tuple(i.left, i.right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  return GenericTestMain(args, "interval_add.cc", "interval_add.tsv",
                         &AddInterval, DefaultComparator{}, param_names);
}
