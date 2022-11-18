// https://leetcode.com/problems/least-operators-to-express-number/

#include <iostream>

#define lli long long int

class Solution {
public:
  int leastOpsExpressTarget(long long int x, long long int target) {
    return f(x, target);
  }

  int f(long long int x, long long int target) {
    if (target < x) {
      return std::min(2 * target - 1, 2 * (x - target));
    }

    long long int curr_power = 1;
    int count = 0;
    while (curr_power * x <= target) {
      curr_power *= x;
      count++;
    }

    if (curr_power == target) return count - 1;

    int k1 = target / curr_power;
    int opt1 = (
      target % curr_power == 0
      ? k1 * count - 1
      : k1 * count + f(x, target - k1 * curr_power)
    );

    long long int target_opt2 = curr_power * x - target;
    int k2 = target_opt2 / curr_power;
    int opt2 = (
      target_opt2 % curr_power == 0
      ? (k2 + 1) * count
      : (k2 + 1) * count + f(x, target_opt2 - k2 * curr_power) + 1
    );

    return std::min(opt1, opt2);
  }
};