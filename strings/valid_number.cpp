// https://leetcode.com/problems/valid-number/

#include <iostream>

bool valid_decimal(std::string str) {
  int digits_before_dot = 0;
  int digits_after_dot = 0;
  bool dot = false;
  for (int i = 0; i < str.length(); i++) {
    if (i == 0 && (str[i] == '+' || str[i] == '-')) continue;
    
    if (str[i] == '.') {
      if (dot) return false;
      dot = true;
      continue;
    }

    if (0 > str[i] - '0' || str[i] - '0' > 9) return false;
    
    if (dot) digits_after_dot++;
    else digits_before_dot++;
  }

  return digits_before_dot > 0 || digits_after_dot > 0;
}

bool valid_number(std::string str) {
  int digits = str.length();
  for (int i = 0; i < str.length(); i++) {
    if (i == 0 && (str[i] == '+' || str[i] == '-')) {
      digits--;
      continue;
    }
    if (0 > str[i] - '0' || str[i] - '0' > 9) return false;
  }

  return digits > 0;
}

bool solve(std::string s) {
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'e' || s[i] == 'E') {
      if (i == 0) return false;

      std::string first_part = s.substr(0, i);
      std::string last_part = s.substr(i + 1);
      return (valid_decimal(first_part) || valid_number(first_part)) && valid_number(last_part);
    }
  }

  return valid_decimal(s) || valid_number(s);
}

int main()
{
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string s;
  std::cin >> s;
  std::cout << solve(s) << std::endl;

  return 0;
}