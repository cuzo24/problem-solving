// https://omegaup.com/arena/problem/X-AE-A-12-Musk/

#include <iostream>
#include <vector>
#include <stack>

std::vector<int> solve(const std::vector<int>&, const std::vector<int>&);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int t;
  const int MAX_N = 1e5;
  std::cin >> t;

  while (t--) {
    int input, n;
    std::cin >> n;
    std::vector<int> nums(n);
    std::vector<int> freqs(MAX_N, 0);

    for (int i = 0; i < n; i++) {
      std::cin >> input;
      nums[i] = input;
      freqs[input]++;
    }

    std::vector<int> answers = solve(nums, freqs);
    for (int i = 0; i < n; i++) {
      std::cout << answers[i] << (i == n - 1 ? "\n" : " ");
    }
  }

  return 0;
}

std::vector<int> solve(const std::vector<int> &nums, const std::vector<int> &freqs) {
  int length = nums.size();
  std::vector<int> answers(length, -1);
  std::stack<int> st;

  for (int i = 0; i < length; i++) {
    while (!st.empty() && freqs[nums[i]] > freqs[nums[st.top()]]) {
      answers[st.top()] = nums[i];
      st.pop();
    }

    st.push(i);
  }
  return answers;
}