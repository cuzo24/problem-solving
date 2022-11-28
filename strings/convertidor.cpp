// https://omegaup.com/arena/problem/OMI2018-Convertidor/

#include <iostream>
#include <vector>

#define lli long long unsigned int

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int max_length = 14, alphabet_size = 26;
  std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::vector<lli> powers(max_length, 1);

  for (int i = 1; i < max_length; i++) {
    powers[i] = powers[i - 1] * alphabet_size;
  }

  int type;
  std::cin >> type;
  if (type == 0) {
    lli number;
    std::string answer = "";

    std::cin >> number;
    int len = 0;

    for (int i = 0; i < max_length; i++) {
      if (number < powers[i]) break;
      number -= powers[i];
      len++;
    }

    for (int i = 0; i < len; i++) {
      int letter_index = number / powers[len - i - 1];
      number -= letter_index * powers[len - i - 1];
      answer += alphabet[letter_index];
    }

    std::cout << answer << std::endl;
  } else {
    std::string str;
    lli answer = 0;
    const lli m = 1e9;
    lli aux = 0;

    std::cin >> str;
    for (int i = 0; i < str.length(); i++) {
      if (str[i] != 'A') answer += powers[str.length() - i - 1] * (str[i] - 'A');
    }

    for (int i = 0; i < str.length(); i++) {
      answer += powers[i];
    }

    if (answer >= m) {
      aux += answer / m;
      answer %= m;
    }

    if (aux == 0) {
      std::cout << answer << std::endl;
    } else {
      std::string left = std::to_string(aux);
      std::string right = std::to_string(answer);
      if (right.length() < 9) {
        right = std::string(9 - right.length(), '0') + right;
      }
      std::cout << left << right << std::endl;
    }
  }
  return 0;
}