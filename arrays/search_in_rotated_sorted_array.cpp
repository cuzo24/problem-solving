// https://leetcode.com/problems/search-in-rotated-sorted-array/

#include <iostream>
#include <vector>

class Solution {
public:
  int search(const std::vector<int> &nums, int target) {
    int start = 0, end = nums.size() - 1;

    while (start <= end) {
      int middle = (end - start) / 2 + start;
      if (nums[middle] < target) {
        if (nums[middle] <= nums[end] && nums[end] < target) {
          end = middle - 1;
        } else {
          start = middle + 1;
        }
      } else if (nums[middle] > target) {
        if (nums[middle] >= nums[start] && nums[start] > target) {
          start = middle + 1;
        } else {
          end = middle - 1;
        }
      } else {
        return middle;
      }
    }

    return -1;
  }
};

int main() {
  return 0;
}