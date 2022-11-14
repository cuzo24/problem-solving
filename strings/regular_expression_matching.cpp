// https://leetcode.com/problems/regular-expression-matching/

#include <iostream>

class Solution {
public:
  bool is_match(const std::string &s, const std::string p) {
    std::string pattern = reduce(p);
    return is_match_helper(s, pattern, 0, 0);
  }

  bool is_match_helper(const std::string &str, const std::string &pattern, int ptr1, int ptr2) {
    if (ptr1 == str.length()) {
      if (ptr2 == pattern.length()) return true;
      else if (ptr2 + 1 < pattern.length() && pattern[ptr2 + 1] == '*') {
        return is_match_helper(str, pattern, ptr1, ptr2 + 2);
      } else return false;
    }

    if (ptr2 == pattern.length()) return false;

    if (ptr2 + 1 < pattern.length() && pattern[ptr2 + 1] == '*') {
      if (pattern[ptr2] == str[ptr1] || pattern[ptr2] == '.') {
        return (
          is_match_helper(str, pattern, ptr1 + 1, ptr2) ||
          is_match_helper(str, pattern, ptr1, ptr2 + 2)
        );
      }
      return is_match_helper(str, pattern, ptr1, ptr2 + 2);
    } else if (pattern[ptr2] == str[ptr1] || pattern[ptr2] == '.') {
      return is_match_helper(str, pattern, ptr1 + 1, ptr2 + 1);
    }

    return false;
  }

  std::string reduce(const std::string &p) {
    std::string result = "";
    for (int i = 0; i < p.length(); i++) {
      if (i > 0 && p[i - 1] == '*' && p[i] == '*') continue;
      result += p[i];
    }
    return result;
  }
};