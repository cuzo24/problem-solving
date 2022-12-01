// https://leetcode.com/problems/time-needed-to-inform-all-employees/

#include <iostream>
#include <vector>

class Solution {
public:
  int numOfMinutes(
      int n, int head_id, const std::vector<int> &manager,
      const std::vector<int> &inform_times
  ) {
    std::vector<std::vector<int>> adj_list(n, std::vector<int> ());
    for (int i = 0; i < n; i++) {
      if (i == head_id) continue;
      adj_list[manager[i]].push_back(i);
    }

    return get_num_of_minutes(adj_list, inform_times, 0, head_id);
  }

  int get_num_of_minutes(
      const std::vector<std::vector<int>> &adj_list,
      const std::vector<int> &inform_times,
      int curr_time, int curr_employee
  ) {
    if (adj_list[curr_employee].size() == 0) return curr_time;

    int max_time = curr_time, time_needed = inform_times[curr_employee];
    for (int subordinate : adj_list[curr_employee]) {
      max_time = std::max(
          max_time, get_num_of_minutes(adj_list, inform_times, curr_time + time_needed, subordinate)
      );
    }

    return max_time;
  }
};