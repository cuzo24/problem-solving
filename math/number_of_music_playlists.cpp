// https://leetcode.com/problems/number-of-music-playlists/

#include <iostream>
#include <vector>

#define lli long long int
const lli MOD = 1e9 + 7;

class Solution {
public:
  lli numMusicPlaylists(int n, int goal, int k) {
    const int max_n = 100;
    std::vector<std::vector<lli>> binomial_coeff(max_n + 1, std::vector<lli> ());
    std::vector<lli> factorials(max_n + 1, 1);

    for (int i = 1; i <= max_n; i++) {
      factorials[i] = factorials[i - 1] * i;
      if (factorials[i] >= MOD) factorials[i] %= MOD;
    }

    for (int i = 0; i <= max_n; i++) {
      binomial_coeff[i].resize(i + 1);
      for (int j = 0; j <= i; j++) {
        if (j == 0 || j == i) {
          binomial_coeff[i][j] = 1;
        } else {
          lli curr_fact = binomial_coeff[i - 1][j - 1] + binomial_coeff[i - 1][j];
          if (curr_fact >= MOD) curr_fact -= MOD;
          binomial_coeff[i][j] = curr_fact;
        }
      }
    }

    lli sign = 1, answer = 0;
    for (int i = n; i >= k; i--) {
      answer += sign * playlists_with_at_most_m_songs(
          i, goal, n, k, factorials, binomial_coeff
      );

      sign *= -1;
      if (answer < 0) answer += MOD;
      else if (answer >= MOD) answer -= MOD;
    }

    return answer;
  }

  lli playlists_with_at_most_m_songs(
    int m, int goal, int n, int k, const std::vector<lli> &factorials,
    const std::vector<std::vector<lli>> &binomial_coeff
  ) {
    lli answer = binomial_coeff[n][m] * binomial_coeff[m][k];
    if (answer >= MOD) answer %= MOD;

    answer *= factorials[k];
    if (answer >= MOD) answer %= MOD;

    answer *= m_pow(m - k, goal - k);
    if (answer >= MOD) answer %= MOD;

    return answer;
  }

  lli m_pow(lli base, lli exp) {
    lli exp_power = base, answer = 1;
    while (exp) {
      if ((exp & 1) == 1) {
        answer *= exp_power;
        if (answer >= MOD) answer %= MOD;
      }

      exp >>= 1;
      exp_power *= exp_power;
      if (exp_power >= MOD) exp_power %= MOD;
    }

    return answer;
  }
};