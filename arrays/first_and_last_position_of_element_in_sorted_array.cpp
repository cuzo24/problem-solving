// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> search_range(const std::vector<int> &nums, int target) {
    std::vector<int> range = {-1, -1};
    int start = find_gte(nums, target);
    int end = find_gte(nums, target + 1);

    if (start != end) {
      range[0] = start;
      range[1] = (end == -1 ? nums.size() : end) - 1;
    }
  
    return range;
  }

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
};

int main() {
  return 0;
}