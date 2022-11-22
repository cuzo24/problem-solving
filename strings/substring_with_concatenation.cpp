// https://leetcode.com/problems/substring-with-concatenation-of-all-words/

#include <iostream>
#include <vector>
#include <map>

#define lli long long int
const lli MOD = 1e9 + 9;

lli get_hash(const std::string&);
std::vector<lli> get_all_subhashes(const std::string&);
lli mpow(lli, lli);

class Solution {
public:
  std::vector<int> findSubstring(std::string s, const std::vector<std::string> &words) {
    std::map<lli, int> mp;
    int word_length = words[0].size();

    if (word_length * words.size() > s.length()) return std::vector<int> ();

    for (int i = 0; i < words.size(); i++) {
      lli hash = get_hash(words[i]);
      std::map<lli, int>::iterator it = mp.find(hash);
      if (it != mp.end()) {
        it->second++;
      } else {
        mp.insert(std::make_pair(hash, 1));
      }
    }

    std::vector<lli> subhashes = get_all_subhashes(s);
    std::vector<lli> occurrences = get_occurrences(subhashes, mp, word_length);

    std::vector<int> answer;

    for (int i = 0; i < word_length; i++) {
      std::map<lli, int> aux_mp;
      int included = 0;
      for (int j = 0; i + word_length * j < s.length(); j++) {
        // First we have to remove the element that is no longer part of the current substring
        if (j >= words.size()) {
          lli hash_to_remove = occurrences[i + word_length * (j - words.size())];;
          if (hash_to_remove != -1) {
            // No need to check if it is inside our temporal map because we added it previously
            aux_mp[hash_to_remove]--;
            std::map<lli, int>::iterator it = mp.find(hash_to_remove);
            included -= aux_mp[hash_to_remove] < it->second ? 1 : 0;
          }
        }

        lli current_hash = occurrences[i  + word_length * j];
        if (current_hash == -1) continue;
        std::map<lli, int>::iterator aux_it = aux_mp.find(current_hash);
        std::map<lli, int>::iterator it = mp.find(current_hash);
        if (aux_it != aux_mp.end()) {
          aux_it->second++;
          included += aux_it->second <= it->second ? 1 : 0;
        } else {
          aux_mp.insert(std::make_pair(current_hash, 1));
          included++;
        }

        if (j + 1 >= words.size() && included == words.size()) {
          answer.push_back(i + word_length * (j - words.size() + 1));
        }
      }
    }

    return answer;
  }

  std::vector<lli> get_occurrences(
      const std::vector<lli> &subhashes,
      std::map<lli, int> &mp,
      int word_length
  ) {
    std::vector<lli> answer(subhashes.size(), -1);

    std::vector<lli> powers;
    lli power = 1;
    for (int i = 0; i < subhashes.size(); i++) {
      powers.push_back(power);
      power *= 31;
      if (power >= MOD) power %= MOD;
    }

    for (int i = word_length - 1; i < subhashes.size(); i++) {
      lli curr_hash;

      if (i == word_length - 1) {
        curr_hash = subhashes[i];
      } else {
        lli power_inverse = mpow(powers[i - word_length + 1], MOD - 2);
        curr_hash = subhashes[i] - subhashes[i - word_length];
        if (curr_hash < 0 ) curr_hash += MOD;
        curr_hash = (curr_hash * power_inverse) % MOD;
      }

      std::map<lli, int>::iterator it = mp.find(curr_hash);
      if (it != mp.end()) {
        answer[i - word_length + 1] = it->first;
      }
    }
    return answer;
  }
};

lli get_hash(const std::string &str) {
  lli result = 0;
  lli curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    result += curr_pow * (str[i] - 'a' + 1);
    curr_pow *= 31;
    if (result >= MOD) result %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}

std::vector<lli> get_all_subhashes(const std::string &str) {
  std::vector<lli> result;
  lli curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    lli curr_val = curr_pow * (str[i] - 'a' + 1) + (i > 0 ? result[i - 1] : 0);

    result.push_back(curr_val);
    curr_pow *= 31;
    if (result[i] >= MOD) result[i] %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}

lli mpow(lli a, lli b) {
  lli x = 1;
  while (b > 0) {
    if (b & 1) {
      x = (x * a) % MOD;
    }
    a = (a * a) % MOD;
    b >>= 1;
  }
  return x;
}