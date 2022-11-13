// https://leetcode.com/problems/naming-a-company/

#include <iostream>
#include <vector>
#include <set>

#define lli long long int
const lli MOD = 1e9 + 9;

lli get_hash(const std::string&, int);

class Solution {
public:
  lli distinct_names(std::vector<std::string> &ideas) {
    std::set<std::pair<lli, lli>> hashes;
    std::vector<int> letter_occurrences(26, 0);
    std::vector<std::vector<int>> compatibles(26);
    lli answer = 0;

    for (int i = 0; i < ideas.size(); i++) {
      hashes.insert(std::make_pair(get_hash(ideas[i], 29), get_hash(ideas[i], 31)));
      letter_occurrences[ideas[i][0] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
      compatibles[i] = std::vector<int> (26, letter_occurrences[i]);
    }

    for (int i = 0; i < ideas.size(); i++) {
      int prefix = ideas[i][0] - 'a';
      lli suffix_hash_pow29 = get_hash(ideas[i], 29) - prefix;
      lli suffix_hash_pow31 = get_hash(ideas[i], 31) - prefix;
      for (int j = 0; j < 26; j++) {
        std::set<std::pair<lli, lli>>::iterator it;
        it = hashes.find({suffix_hash_pow29 + j, suffix_hash_pow31 + j});
        if (it != hashes.end()) {
          compatibles[prefix][j]--;
        }
      }
    }

    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        answer += (1LL * compatibles[i][j] * compatibles[j][i]);
      }
    }

    return answer;
  }
};

int main() {
  return 0;
}

lli get_hash(const std::string &str, int pow = 29) {
  lli result = 0;
  lli curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    result += curr_pow * (str[i] - 'a' + 1);
    curr_pow *= pow;
    if (result >= MOD) result %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}