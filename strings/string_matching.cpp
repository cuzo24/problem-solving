// https://cses.fi/problemset/task/1753

#include <iostream>
#include <vector>

#define ll long long
const ll int MOD = 1e9 + 9;

ll int get_hash(const std::string&);
std::vector<ll int> get_all_subhashes(const std::string&);
ll int get_occurrences(const std::string&, const std::string&);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string str, pattern;
  std::getline(std::cin, str);
  std::getline(std::cin, pattern);

  // std::cout << std::endl << str << " " << pattern << std::endl;
  // std::cout << std::endl << str.length() << " " << pattern.length() << std::endl;
  
  std::cout << get_occurrences(str, pattern) << std::endl;
  return 0;
}

ll int get_occurrences(const std::string &str, const std::string &pattern) {  
  ll int answer = 0;
  std::vector<ll int> hashes = get_all_subhashes(str);
  ll int hash = get_hash(pattern);

  std::vector<ll int> powers;
  ll int power = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    powers.push_back(power);
    power *= 31;
    if (power >= MOD) power %= MOD;
  }

  for (unsigned int i = 0; i < str.length() - pattern.length() + 1; i++) {
    ll int curr_hash = hash * powers[i];
    if (curr_hash >= MOD) curr_hash %= MOD;
    ll int sum = curr_hash + (i > 0 ? hashes[i - 1] : 0);
    if (sum >= MOD) sum %= MOD;
    if (sum == hashes[i + pattern.length() - 1]) answer++; 
  }
  return answer;
}

ll int get_hash(const std::string &str) {
  ll int result = 0;
  ll int curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    result += curr_pow * (str[i] - 'a' + 1);
    curr_pow *= 31;
    if (result >= MOD) result %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}

std::vector<ll int> get_all_subhashes(const std::string &str) {
  std::vector<ll int> result;
  ll int curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    ll int curr_val = curr_pow * (str[i] - 'a' + 1) + (i > 0 ? result[i - 1] : 0); 

    result.push_back(curr_val);
    curr_pow *= 31;
    if (result[i] >= MOD) result[i] %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}