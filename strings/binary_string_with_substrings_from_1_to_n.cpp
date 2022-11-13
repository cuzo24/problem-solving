// https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/

#include <iostream>
#include <set>

class Solution {
public:
  bool query_string(std::string &s, int n) {
    // given the constraints of len(s) <= 1000 we can infer that if n >= 2048 = 2^11 then it would be
    // impossible to get all possible permutations of length 11 starting with a 1 (which are 1024)
    // because we have at most 1000 - 12 + 1 = 989 substrings of length 12.
    // There is probably a better lower bound, but this is good enough. All there is left to do is
    // check if the substrings of at most length 11 in the range [1, n] are all present
    if (n >= 2048) return false;

    std::set<int> included;
    for (int i = 0; i < s.length(); i++) {
      for (int j = 0; j < get_binary_length(n) && i + j < s.length(); j++) {
        int current_binary = get_binary(s, i, i + j);
        if (!(1 <= current_binary && current_binary <= n)) continue;

        std::set<int>::iterator it = included.find(current_binary);
        if (it == included.end()) {
          included.insert(current_binary);
        }
      }
    }

    return included.size() == n;
  }

  int get_binary_length(int n) {
    int answer = 1, curr_pow = 2;
    while (n > curr_pow - 1) {
      curr_pow *= 2;
      answer++;
    }

    return answer;
  }

  int get_binary(std::string &s, int starting_index, int ending_index) {
    int curr_pow = 1, answer = 0;
    for (int i = ending_index; i >= starting_index; i--) {
      if (s[i] == '1') answer += curr_pow;
      curr_pow *= 2;
    }

    return answer;
  }
};

int main() {
  return 0;
}