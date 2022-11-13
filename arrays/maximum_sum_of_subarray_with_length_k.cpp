// https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/

#include <vector>
#include <map>

#define lli long long int

class Solution {
public:
  lli maximum_subarray_sum(const std::vector<int> &nums, int k) {
    lli max = 0;
    std::map<int, int> occurrences;

    int total_repetitions = 0;
    lli curr_sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      curr_sum += nums[i];
      std::map<int, int>::iterator it = occurrences.find(nums[i]);
      if (it == occurrences.end()) {
        occurrences.insert(std::make_pair(nums[i], 1));
      } else {
        it->second++;
        total_repetitions++;
      }

      if (i >= k) {
        curr_sum -= nums[i - k];
        it = occurrences.find(nums[i - k]);
        if (it->second == 1) {
          occurrences.erase(nums[i - k]);
        } else {
          it->second--;
          total_repetitions--;
        }
      }

      if (i + 1 >= k && curr_sum > max && total_repetitions == 0) {
        max = curr_sum;
      }
    }

    return max;
  }
};