// https://omegaup.com/arena/problem/Paisajes-de-la-ciudad/

#include <iostream>
#include <vector>
#include <stack>

std::vector<int> solve(const std::vector<int>&);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> nums(n);

  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::vector<int> answers = solve(nums);
  for (int i = 0; i < n; i++) {
    std::cout << answers[i] << (i == n - 1 ? "\n" : " ");
  }

  return 0;
}

std::vector<int> solve(const std::vector<int> &nums) {
  int len = nums.size();
  std::vector<int> first_greater_left(len, -1);
  std::vector<int> first_greater_right(len, len);
  std::stack<int> st_left, st_right;

  for (int i = 0; i < len; i++) {
    while (!st_left.empty() && nums[len - i - 1] > nums[st_left.top()]) {
      first_greater_left[st_left.top()] = len - i - 1;
      st_left.pop();
    }

    while (!st_right.empty() && nums[i] > nums[st_right.top()]) {
      first_greater_right[st_right.top()] = i;
      st_right.pop();
    }

    st_left.push(len - i - 1);
    st_right.push(i);
  }

  std::vector<int> answers(len);
  for (int i = 0; i < len; i++) {
    answers[i] = first_greater_right[i] - first_greater_left[i] - 1;
  }
  return answers;
}