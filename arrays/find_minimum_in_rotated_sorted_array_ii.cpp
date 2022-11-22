// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

#include <iostream>
#include <vector>

class Solution {
public:
  int findMin(const std::vector<int> &nums) {
    int minimum = nums[0];
    binary_search(nums, 0, nums.size() - 1, minimum);
    return minimum;
  }

  void binary_search(const std::vector<int> &nums, int start, int end, int &minimum) {
    if (start > end) return;

    int middle = (end - start) / 2 + start;
    if (nums[middle] < minimum) {
      minimum = nums[start];

      if (nums[middle] > nums[start]) {
        // Non-decreasing from start to middle
        // nums[start] is the smallest in the range, so we can continue looking in the other segment
        binary_search(nums, middle + 1, end, minimum);
      } else if (nums[middle] < nums[start]) {
        minimum = nums[middle];
        binary_search(nums, start + 1, middle - 1, minimum);
      } else {
        if (nums[end] > nums[middle]) return;

        if (nums[end] < nums[middle]) {
          minimum = nums[end];
          binary_search(nums, middle + 1, end - 1, minimum);
        } else {
          binary_search(nums, middle + 1, end - 1, minimum);
          binary_search(nums, start + 1, middle - 1, minimum);
        }
      }
    } else if (nums[middle] >= minimum) {
      // nums[start], nums[start + 1], ..., nums[middle] is non-decreasing
      if (nums[middle] > nums[start]) {
        if (nums[start] < minimum) {
          // We are only interested in the minimum of this segment
          minimum = nums[start];
        }
        binary_search(nums, middle + 1, end, minimum);
      } else if (nums[middle] < nums[start]) {
        binary_search(nums, start + 1, middle - 1, minimum);
      } else {
        if (nums[end] > nums[middle]) return;

        if (nums[end] < nums[middle]) {
          minimum = nums[end];
          binary_search(nums, middle + 1, end - 1, minimum);
        } else {
          binary_search(nums, middle + 1, end - 1, minimum);
          binary_search(nums, start + 1, middle - 1, minimum);
        }
      }
    }
  }
};