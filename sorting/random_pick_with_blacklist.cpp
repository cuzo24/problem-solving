// https://leetcode.com/problems/random-pick-with-blacklist/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>

int find_gte(const std::vector<int> &nums, int target) {
  int start = 0, end = nums.size() - 1, result = -1;
  while (start <= end) {
    int middle = (end - start) / 2 + start;
    if (nums[middle] >= target) {
      end = middle - 1;
      result = middle;
    } else {
      start = middle + 1;
    }
  }

  return result;
}

class Solution {
public:
  std::vector<int> not_blacklisted_until_index;
  int range;

  Solution(int n, std::vector<int> &blacklist) {
    srand(time(0));
    int size = blacklist.size();

    not_blacklisted_until_index = blacklist;
    sort(not_blacklisted_until_index.begin(), not_blacklisted_until_index.end());

    for (int i = 0; i < size; i++) {
      not_blacklisted_until_index[i] -= i;
    }
    range = n - size;
  }
  
  int pick() {
    int number = (rand() % range) + 1;
    if (not_blacklisted_until_index.size() == 0) return number - 1;
    int position = find_gte(not_blacklisted_until_index, number);

    return number - 1 + (position == -1 ? not_blacklisted_until_index.size() : position);
  }
};

int main() {
  return 0;
}