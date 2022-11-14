// https://leetcode.com/problems/longest-valid-parentheses/

#include <iostream>
#include <vector>
#include <map>

class SparseTable {
public:
  std::vector<std::vector<int>> minimums;
  std::vector<int> log;

  SparseTable(const std::vector<int> &data) {
    log.resize(data.size() + 1, 0);
    for (int i = 2; i <= data.size(); i++) {
      log[i] = log[i/2] + 1;
    }

    minimums.resize(16);
    minimums[0] = data;
    for (int i = 1; i <= 15; i++) {
      minimums[i].resize(data.size());
      for (int j = 0; j + (1 << i) <= data.size(); j++) {
        minimums[i][j] = std::min(minimums[i - 1][j], minimums[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  int query(int left, int right) {
    int i = log[right - left + 1];
    return std::min(minimums[i][left], minimums[i][right - (1 << i) + 1]);
  }
};

class Solution {
public:
  int longestValidParentheses(std::string &s) {
    std::map<int, std::vector<int>> freq;
    freq.insert({0, std::vector<int> (1, -1)});
    std::vector<int> data;

    for (int i = 0; i < s.length(); i++) {
      if (i == 0) {
        data.push_back(s[i] == '(' ? 1 : -1);
      } else {
        data.push_back(data[i - 1] + (s[i] == '(' ? 1 : -1));
      }

      std::map<int, std::vector<int>>::iterator it = freq.find(data[i]);
      if (it == freq.end()) {
        freq.insert({data[i], std::vector<int> (1, i)});
      } else {
        it->second.push_back(i);
      }
    }

    SparseTable *sp = new SparseTable(data);

    int longest = 0;
    for (auto i = freq.begin(); i != freq.end(); i++) {
      std::vector<int> arr = i->second;
      if (arr.size() == 1) continue;

      bool is_previous_valid = false;
      int curr_length = 0;
      for (int j = 1; j < arr.size(); j++) {
        int minimum = sp->query(arr[j - 1] + 1, arr[j]);
        if (minimum >= i->first) {
          curr_length += arr[j] - arr[j - 1];
          is_previous_valid = true;

          if (curr_length > longest) {
            longest = curr_length;
          }
        } else {
          curr_length = 0;
          is_previous_valid = false;
        }
      }
    }

    return longest;
  }
};