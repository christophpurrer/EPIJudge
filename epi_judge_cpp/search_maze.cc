#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kWhite, kBlack };
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

bool isFeasible(const Coordinate &cur, vector<vector<Color>> &maze) {
    return cur.x >= 0 && cur.x < maze.size() && cur.y >= 0 && cur.y < maze[cur.x].size() &&
           maze[cur.x][cur.y] == Color::kWhite;
}

void SearchMazeHelperWorking(vector<vector<Color>> &maze, const Coordinate &s,
                      const Coordinate &e, std::vector<Coordinate> partial, std::vector<Coordinate> &result) {

    // Base case
    // Found (a better) solution
    partial.emplace_back(s);
    if (s == e && (result.empty() || partial.size() < result.size())) {
        result = partial;
        return;
    }

    // Recursive case(s)
    // Can go up?
    {
        Coordinate up{s.x, s.y + 1};
        if (isFeasible(up, maze)) {
            maze[up.x][up.y] = Color::kBlack;
            SearchMazeHelperWorking(maze, up, e, partial, result);
        }
    }

    // Can go down?
    {
        Coordinate down{s.x, s.y - 1};
        if (isFeasible(down, maze)) {
            maze[down.x][down.y] = Color::kBlack;
            SearchMazeHelperWorking(maze, down, e, partial, result);
        }
    }

    // Can go right?
    {
        Coordinate right{s.x + 1, s.y};
        if (isFeasible(right, maze)) {
            maze[right.x][right.y] = Color::kBlack;
            SearchMazeHelperWorking(maze, right, e, partial, result);
        }
    }

    // Can go left?
    {
        Coordinate left{s.x - 1, s.y};
        if (isFeasible(left, maze)) {
            maze[left.x][left.y] = Color::kBlack;
            SearchMazeHelperWorking(maze, left, e, partial, result);
        }
    }
}

void SearchMazeHelper(vector<vector<Color>> &maze, const Coordinate &s,
                      const Coordinate &e, std::vector<Coordinate> partial, std::vector<Coordinate> &result) {


    // Enqueue current field and mark as visited
    maze[s.x][s.y] = Color::kBlack;
    partial.emplace_back(s);
    // Base case
    // Found (a better) solution
    if (s == e && (result.empty() || partial.size() < result.size())) {
        result = partial;
        return;
    }

    // Recursive case(s)
    // Can go up/down/left/right?
    const std::array<std::pair<int, int>, 4> steps = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    for (auto step: steps) {
        Coordinate next{s.x + step.first, s.y + step.second};
        if (isFeasible(next, maze)) {
            SearchMazeHelperWorking(maze, next,
                                    e, partial, result);
        }
    }
}

vector<Coordinate> SearchMaze(vector<vector<Color>>& maze, const Coordinate &s,
                              const Coordinate &e) {
    std::vector<Coordinate> partial;
    std::vector<Coordinate> result;
    SearchMazeHelper(maze, s, e, partial, result);
    return result;
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
