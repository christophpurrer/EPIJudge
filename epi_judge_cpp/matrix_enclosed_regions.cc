#include <stdexcept>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

void FillSurroundedRegions(vector<vector<char>> *board_ptr) {
    vector<vector<char>> &board = *board_ptr;
    // Take all 'W' at the border and enqueue them
    std::queue<std::pair<int, int>> q;
    for (int x = 0; x < board.size(); x++) {
        if (board[x][0] == 'W') {
            q.emplace(std::pair<int, int>{x, 0});
        }
        if (board[x][board[x].size() - 1] == 'W') {
            q.emplace(std::pair<int, int>{x, board[x].size() - 1});
        }
    }
    for (int y = 0; y < board[0].size(); y++) {
        if (board[0][y] == 'W') {
            q.emplace(std::pair<int, int>{0, y});
        }
        if (board[board.size() - 1][y] == 'W') {
            q.emplace(std::pair<int, int>{board.size() - 1, y});
        }
    }

    // Mark them 'G' (or any other other all)
    const std::array<std::pair<int, int>, 4> dirs = {{{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};
    while (!q.empty()) {
        auto val = q.front();
        q.pop();
        board[val.first][val.second] = 'G';
        for (auto dir: dirs) {
            auto next = std::pair<int, int>{val.first + dir.first, val.second + dir.second};
            if (next.first >= 0 && next.second >= 0 && next.first < board.size() &&
                next.second < board[next.first].size() && board[next.first][next.second] == 'W') {
                q.emplace(next);
            }
        }
    }

    // Now mark all 'G' as 'W' and the rest 'B'
    for (auto &row: board) {
        for (auto &col : row) {
            col = col == 'G' ? 'W' : 'B';
        }
    }
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
