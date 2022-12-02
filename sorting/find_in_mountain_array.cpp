// https://leetcode.com/problems/find-in-mountain-array/

// This is the MountainArray's API interface.
class MountainArray {
public:
  int get(int index);
  int length();
};


class Solution {
public:
  int findInMountainArray(int target, MountainArray &mountain_arr) {
    // First we find the top of the mountain
    int length = mountain_arr.length();
      int start = 0, end = length - 1, top;
      while (start + 1 < end) {
        int middle = (end - start) / 2 + start;
        int left = mountain_arr.get(middle - 1);
        int center = mountain_arr.get(middle);

        if (left > center) {
          end = middle;
          continue;
        }

        int right = mountain_arr.get(middle + 1);

        if (right > center) {
          start = middle;
          continue;
        }

        if (target == center) return middle;
        top = middle;
        break;
      }

    int left = binary_search(target, mountain_arr, 0, top - 1);
    if (left != -1) return left;

    int right = binary_search(target, mountain_arr, top + 1, length - 1, false);
    if (right != -1) return right;

    return -1;
  }

  int binary_search(int target, MountainArray &mountain_arr, int start, int end, bool increasing = true) {
    int answer = -1;
    while (start <= end) {
      int middle = (end - start) / 2 + start;
      int value = mountain_arr.get(middle);

      if ((value < target && increasing) || (value > target && !increasing)) {
        start = middle + 1;
      } else if ((value > target && increasing) || (value < target && !increasing)) {
        end = middle - 1;
      } else {
        answer = middle;
        break;
      }
    }

    return answer;
  }
};