// https://leetcode.com/problems/spiral-matrix/

#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> spiral_order(const std::vector<std::vector<int>> &matrix) {
    std::vector<int> order;

    int smallest_size = std::min(matrix.size(), matrix[0].size());
    for (int i = 0; i < (smallest_size + 1) / 2; i++) {
      for (int x = i; x < matrix[0].size() - i; x++) {
        order.push_back(matrix[i][x]);
      }
      for (int y = i + 1; y < matrix.size() - i; y++) {
        order.push_back(matrix[y][matrix[0].size() - i - 1]);
      }

      if (i != matrix.size() - i - 1) {
        for (int x = matrix[0].size() - i - 2; x >= i; x--) {
          order.push_back(matrix[matrix.size() - i - 1][x]);
        }
      }

      if (i != matrix[0].size() - i - 1) {
        for (int y = matrix.size() - i - 2; y >= i + 1; y--) {
          order.push_back(matrix[y][i]);
        }
      }
    }

    return order;
  }
};

int main() {
  return 0;
}