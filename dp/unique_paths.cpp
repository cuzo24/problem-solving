// https://leetcode.com/problems/unique-paths/

#include <iostream>
#include <vector>

class Solution {
public:
  // The answer is (m + n - 2) choose (n - 1), but the point is using dp
  int unique_paths(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int> (n));
    return partial_paths(m - 1, n - 1, dp);
  }

private:
  int partial_paths(int i, int j, std::vector<std::vector<int>> &dp) {
    if (i == 0 || j == 0) return dp[i][j] = 1;
    if (!dp[i - 1][j]) partial_paths(i - 1, j, dp);
    if (!dp[i][j - 1]) partial_paths(i, j - 1, dp);
    return dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
  }
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int m, n;
  std::cin >> m >> n;

  Solution o;
  std::cout << o.unique_paths(m, n) << std::endl;
  return 0;
}