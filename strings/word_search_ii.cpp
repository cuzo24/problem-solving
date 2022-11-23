// https://leetcode.com/problems/word-search-ii/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#define lli long long int
const lli MOD = 1e9 + 9;

lli get_hash(const std::string&, int);

class Solution {
public:
  std::vector<std::string> findWords(
      std::vector<std::vector<char>>& board, std::vector<std::string>& words
  ) {
    std::vector<bool> visited(board.size() * board[0].size(), false);
    std::unordered_set<lli> partial_hashes;
    std::unordered_map<lli, std::string> hashes;
    int max_word_length = 10, prime = 29;

    std::vector<lli> powers_prime(max_word_length, 1);
    for (int i = 1; i < max_word_length; i++) {
      powers_prime[i] = powers_prime[i - 1] * prime;
      if (powers_prime[i] > MOD) powers_prime[i] %= MOD;
    }

    max_word_length = 0;
    for (int i = 0; i < words.size(); i++) {
      int word_length = words[i].size();
      max_word_length = std::max(word_length, max_word_length);
      lli curr_hash = 0;
      for (int j = 0; j < words[i].size(); j++) {
        curr_hash += powers_prime[j] * (words[i][j] - 'a' + 1);
        if (curr_hash >= MOD) curr_hash %= MOD;

        if (j + 1 < words[i].size()) {
          partial_hashes.insert(curr_hash);
        } else {
          hashes.insert(std::make_pair(curr_hash, words[i]));
        }
      }
    }

    std::vector<std::string> answer;
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[0].size(); j++) {
        visited[board[0].size() * i + j] = true;
        dfs(
          board, i, j, visited, 0, max_word_length,
          answer, partial_hashes, hashes, powers_prime
        );
        visited[board[0].size() * i + j] = false;
      }
    }
    return answer;
  }

  void dfs(
      const std::vector<std::vector<char>> &board, int x, int y, std::vector<bool> &visited,
      int curr_length, int max_length, std::vector<std::string> &answer,
      const std::unordered_set<lli> &partial_hashes, std::unordered_map<lli, std::string> &hashes,
      const std::vector<lli> &powers_prime, lli curr_hash = 0
  ) {
    curr_hash += powers_prime[curr_length] * (board[x][y] - 'a' + 1);
    if (curr_hash >= MOD) curr_hash %= MOD;

    std::unordered_map<lli, std::string>::const_iterator map_it = hashes.find(curr_hash);
    if (map_it != hashes.end()) {
      answer.push_back(map_it->second);
      hashes.erase(map_it);
    }

    std::unordered_set<lli>::const_iterator set_it = partial_hashes.find(curr_hash);
    if (set_it == partial_hashes.end()) return;

    curr_length++;
    if (curr_length >= max_length) return;

    if (x > 0 && !visited[board[0].size() * (x - 1) + y]) {
      visited[board[0].size() * (x - 1) + y] = true;
      dfs(
          board, x - 1, y, visited, curr_length, max_length,
          answer, partial_hashes, hashes, powers_prime, curr_hash
      );
      visited[board[0].size() * (x - 1) + y] = false;
    }
    if (x + 1 < board.size() && !visited[board[0].size() * (x + 1) + y]) {
      visited[board[0].size() * (x + 1) + y] = true;
      dfs(
          board, x + 1, y, visited, curr_length, max_length,
          answer, partial_hashes, hashes, powers_prime, curr_hash
      );
      visited[board[0].size() * (x + 1) + y] = false;
    }
    if (y > 0 && !visited[board[0].size() * x + y - 1]) {
      visited[board[0].size() * x + y - 1] = true;
      dfs(
          board, x, y - 1, visited, curr_length, max_length,
          answer, partial_hashes, hashes, powers_prime, curr_hash
      );
      visited[board[0].size() * x + y - 1] = false;
    }
    if (y + 1 < board[0].size() && !visited[board[0].size() * x + y + 1]) {
      visited[board[0].size() * x + y + 1] = true;
      dfs(
          board, x, y + 1, visited, curr_length, max_length,
          answer, partial_hashes, hashes, powers_prime, curr_hash
      );
      visited[board[0].size() * x + y + 1] = false;
    }
  }
};