// https://leetcode.com/problems/cut-off-trees-for-golf-event/description/

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

inline bool available(int x, int y, int rows, int cols) {
  return (0 <= x && x < rows && 0 <= y && y < cols);
}

class Solution {
public:
  int cutOffTree(const std::vector<std::vector<int>> &forest) {
    const int m = forest.size();
    const int n = forest[0].size();
    std::vector<std::pair<int, int>> heights;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (forest[i][j] > 1) heights.push_back(std::make_pair(i, j));
      }
    }

    std::sort(heights.begin(), heights.end(),
        [forest](std::pair<int, int> a, std::pair<int, int> b) {
          return forest[a.first][a.second] < forest[b.first][b.second];
        }
    );

    std::vector<std::pair<int, int>> delta({{-1, 0}, {1, 0}, {0, -1}, {0, 1}});
    std::deque<std::pair<int, int>> q;
    int min_steps = 0, prev_x = 0, prev_y = 0;

    for (int i = 0; i < heights.size(); i++) {
      std::vector<std::vector<int>> distances(m, std::vector<int>(n, -1));
      q.push_back(std::make_pair(prev_x, prev_y));
      distances[prev_x][prev_y] = 0;
      int target_x = heights[i].first, target_y = heights[i].second;

      outer:
      while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop_front();

        for (int i = 0; i < delta.size(); i++) {
          int new_x = x + delta[i].first, new_y = y + delta[i].second;
          if (available(new_x, new_y, m, n) && forest[new_x][new_y] != 0) {
            if (distances[new_x][new_y] == -1) {
              distances[new_x][new_y] = distances[x][y] + 1;
              if (new_x == target_x && new_y == target_y) {
                q.clear();
                goto outer;
              }
              q.push_back(std::make_pair(new_x, new_y));
            }
          }
        }
      }

      if (distances[target_x][target_y] == -1) return -1;

      min_steps += distances[target_x][target_y];
      prev_x = target_x;
      prev_y = target_y;
    }

    return min_steps;
  }
};