#include <deque>
#include <vector>
#include <array>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

bool isFeasible(vector<deque<bool>> &img, int x, int y, bool fromColor) {
    return x >= 0 && y >= 0 && x < img.size() && y < img[x].size() && img[x][y] == fromColor;
}

void FlipColorHelper(vector<deque<bool>> &img, int x, int y, bool fromColor) {
    // Base case: flip color
    img[x][y] = !fromColor;

    // Recursive case(s)
    // Can go up, down, left, right?
    std::array<std::pair<int, int>, 4> dirs{{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};
    for (const auto dir : dirs) {
        std::pair<int, int> next{x + dir.first, y + dir.second};
        if (isFeasible(img, next.first, next.second, fromColor)) {
            FlipColorHelper(img, next.first, next.second, fromColor);
        }
    }
}

void FlipColorRec(int x, int y, vector<deque<bool>> *image_ptr) {
    vector<deque<bool>> &img = *image_ptr;
    const bool fromColor = img[x][y];
    FlipColorHelper(img, x, y, fromColor);
}

// BFS
void FlipColor(int x, int y, vector<deque<bool>> *image_ptr) {
    vector<deque<bool>> &img = *image_ptr;
    const bool fromColor = img[x][y];
    std::array<std::pair<int, int>, 4> dirs{{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};
    std::queue<std::pair<int, int>> q;
    q.emplace(std::pair<int, int>{x, y});
    while (!q.empty()) {
        auto val = q.front();
        q.pop();
        img[val.first][val.second] = !fromColor;
        for (const auto dir : dirs) {
            std::pair<int, int> next{val.first + dir.first, val.second + dir.second};
            if (isFeasible(img, next.first, next.second, fromColor)) {
                q.emplace(next);
            }
        }
    }
}

vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
