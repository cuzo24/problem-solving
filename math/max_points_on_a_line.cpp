// https://leetcode.com/problems/max-points-on-a-line/

#include <iostream>
#include <vector>

class Solution {
public:
  int max_points(const std::vector<std::vector<int>> &points) {
    int len = points.size();
    if (len == 1) return 1;

    int max = 2;
    for (int i = 0; i < len - 1; i++) {
      for (int j = i + 1; j < len; j++) {
        
        int current_points_on_line = 2;
        if (points[i][0] == points[j][0]) {
          for (int k = 0; k < len; k++) {
            if (k == i || k == j) continue;

            if (points[k][0] == points[i][0]) {
              current_points_on_line++;
            }
          }
        } else {
          int y_diff = points[i][1] - points[j][1];
          int x_diff = points[i][0] - points[j][0];
          for (int k = 0; k < len; k++) {
            if (k == i || k == j || points[k][0] == points[i][0]) continue;

            int current_x_diff = points[i][0] - points[k][0];
            int current_y_diff = points[i][1] - points[k][1];
            if (current_x_diff * y_diff == current_y_diff * x_diff) {
              current_points_on_line++;
            }
          }
        }

        if (current_points_on_line > max) {
          max = current_points_on_line;
        }
      }
    }

    return max;
  }
};

int main() {
  return 0;
}