// https://leetcode.com/problems/permutation-sequence/

#include <iostream>
#include <vector>

class Solution {
public:
  std::string get_permutation(int n, int k) {
    std::string answer = "";
    std::vector<int> included(n, false);
    for (int i = 1; i <= n; i++) {
      int factorial = unoptimized_factorial(n - i);
      int divison_res = k / factorial;
      int remainder = k % factorial;
      k = remainder;
      
      if (remainder == 0) {
        k = factorial;
        divison_res--;
      }

      for (int j = 0, count = 0; j < n; j++) {
        if (!included[j]) {
          count++;
          if (count == divison_res + 1) {
            answer += std::to_string(j + 1);
            included[j] = true;
            break;
          }
        }
      }  
    }
    return answer;
  }

  int unoptimized_factorial(int n) {
    if (n <= 1) return 1;
    return unoptimized_factorial(n - 1) * n;
  }
};

int main() {
  Solution o;
  std::cout << o.get_permutation(3, 3) << std::endl;
  std::cout << o.get_permutation(4, 9) << std::endl;
  std::cout << o.get_permutation(3, 1) << std::endl;
  return 0;
}