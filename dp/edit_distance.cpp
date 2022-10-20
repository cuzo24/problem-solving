// https://leetcode.com/problems/edit-distance/

#include <iostream>
#include <vector>

class Solution {
public:
  int min_distance(const std::string &word1, const std::string &word2) {
    int n =  word1.length(),  m = word2.length();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, -1));
    return compute_dp(0, 0, word1, word2, dp);
  }

private:
  int compute_dp(
    int i,
    int j,
    const std::string &word1,
    const std::string &word2,
    std::vector<std::vector<int>> &dp
  ) {
    if (dp[i][j] != -1) return dp[i][j];

    int n = word1.length(), m = word2.length();
    if (i == n || j == m) {
      return dp[i][j] = std::max(n - i, m - j);
    }

    if (word1[i] == word2[j]) {
      return dp[i][j] = compute_dp(i + 1, j + 1, word1, word2, dp);
    }

    return dp[i][j] = 1 + std::min(
      compute_dp(i + 1, j, word1, word2, dp),
      std::min(
        compute_dp(i, j + 1, word1, word2, dp),
        compute_dp(i + 1, j + 1, word1, word2, dp)
      )
    );
  }
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string word1, word2;
  std::cin >> word1 >> word2;

  Solution o;
  std::cout << o.min_distance(word1, word2) << std::endl;
  return 0;
}