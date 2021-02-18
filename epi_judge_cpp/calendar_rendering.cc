#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
    int start, finish;
};

struct Endpoint {
    bool operator<(const Endpoint &other) const {
        return time != other.time ? time < other.time : (isStart && !other.isStart);
    }

    int time;
    bool isStart;
};

int FindMaxSimultaneousEvents(const vector<Event> &A) {
    vector<Endpoint> E;
    for (const auto &event : A) {
        E.emplace_back(Endpoint{event.start, true});
        E.emplace_back(Endpoint{event.finish, false});
    }
    std::sort(E.begin(), E.end());

    int maxSimultaneousEvents = 0, numSimultaneousEvents = 0;
    for (const auto &endpoint : E) {
        if (endpoint.isStart) {
            numSimultaneousEvents++;
            maxSimultaneousEvents = std::max(maxSimultaneousEvents, numSimultaneousEvents);
        } else {
            numSimultaneousEvents--;
        }
    }
    return maxSimultaneousEvents;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
