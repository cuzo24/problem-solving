// https://leetcode.com/problems/distinct-echo-substrings/

#include <iostream>
#include <vector>
#include <set>

#define lli long long int
const lli MOD = 1e9 + 9;

lli get_hash(const std::string&);
std::vector<lli> get_all_subhashes(const std::string&);
lli mpow(lli, lli);
lli get_hash_from_arr(const std::vector<lli>&, const std::vector<lli>&, int, int);

class Solution {
public:
  int distinct_echo_substrings(std::string &text) {
    std::vector<lli> hashes = get_all_subhashes(text);
    std::set<lli> hashes_included;
    int answer = 0;

    std::vector<lli> powers;
    lli power = 1;
    for (int i = 0; i < hashes.size(); i++) {
      powers.push_back(power);
      power *= 31;
      if (power >= MOD) power %= MOD;
    }

    for (int i = 0; i < text.length(); i++) {
      for (int j = 2; i + j <= text.length(); j += 2) {
        lli prefix_hash = get_hash_from_arr(hashes, powers, i, i + j/2 - 1);
        lli suffix_hash = get_hash_from_arr(hashes, powers, i + j/2, i + j - 1);

        if (prefix_hash == suffix_hash) {
          std::set<lli>::iterator it = hashes_included.find(prefix_hash);
          if (it == hashes_included.end()) {
            hashes_included.insert(prefix_hash);
            answer++;
          }
        }
      }
    }

    return answer;
  }
};

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

lli get_hash_from_arr(const std::vector<lli> &arr, const std::vector<lli> &powers, int start, int end) {
  lli hash;
  if (start == 0) {
    hash = arr[end];
  } else {
    lli power_inverse = mpow(powers[start], MOD - 2);
    hash = arr[end] - arr[start - 1];
    if (hash < 0 ) hash += MOD;
    hash = (hash * power_inverse) % MOD;
  }
  return hash;
};