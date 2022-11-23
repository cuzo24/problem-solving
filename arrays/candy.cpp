// https://leetcode.com/problems/candy/

#include <vector>
#include <iostream>

class Solution {
public:
  long long int candy(const std::vector<int> &ratings) {
    int len = ratings.size();
    long long int minimum_candies = 0;
    std::vector<int> longest_increasing_from_left(len, 0);
    std::vector<int> longest_increasing_from_right(len, 0);

    int curr_longest_left = 0, curr_longest_right = 0;
    for (int i = 1; i < len; i++) {
      if (ratings[i - 1] >= ratings[i]) {
        curr_longest_left = 0;
      } else if (ratings[i - 1] < ratings[i]) {
        curr_longest_left++;
        longest_increasing_from_left[i] = curr_longest_left;
      }

      if (ratings[len - i] >= ratings[len - i - 1]) {
        curr_longest_right = 0;
      } else if (ratings[len - i] < ratings[len - i - 1]) {
        curr_longest_right++;
        longest_increasing_from_right[len - i - 1] = curr_longest_right;
      }
    }

    for (int i = 0; i < len; i++) {
      minimum_candies += 1 + (
          std::max(longest_increasing_from_left[i], longest_increasing_from_right[i])
      );
    }

    return minimum_candies;
  }
};